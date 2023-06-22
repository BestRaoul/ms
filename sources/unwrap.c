#include "ms.h"

#define ERROR_MSG SHELL_MSG""

t_dict_int_str_member	*_member(t_list *lexeme)
{
	return ((t_dict_int_str_member *)(lexeme->content));
}

#define IS_REDIR(x) (x == REDIRLEFT||x== REDIRRIGHT||x==APPEND||x==HEREDOCOP)

char *list_2_str(t_list *lst)
{
	int	total_len = 0;
	t_list *i = lst;
	while (i)
	{
		total_len += ft_strlen_int(lst->content);
		i = i->next;
	}
	char *str = MALLOC(total_len + 1);
	int	j = 0;
	i = lst;
	while (i)
	{
		ft_strlcpy(&(str[j]), i->content, ft_strlen_int(i->content) + 1);
		j += ft_strlen_int(i->content);
		i = i->next;
	}
	return (str);
}

//reuses the litst's CONTENT pointers, and sets them NULL
//so no need to free them
char	**list_2_strr(t_list *lst)
{
	char **res = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	int i = 0;
	while (lst)
	{
		res[i++] = lst->content;
		lst->content = NULL;
		lst = lst->next;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_splitf(char *s, int (*next)(char *))
{
	t_list	*strs = NULL;
	int		next_end;

	while (*s)
	{
		next_end = next(s);
		if (next_end > 0)
			ft_lstadd_back(&strs, ft_lstnew(chop(s, next_end - 1)));
		s += next_end;
		if (!*s)
			break;
		s++;
	}
	return (list_2_strr(strs));
}

//can fail, no closing quote -1
int	add_until(t_list **strs_ptr, char *s)
{
	int		next;
	int		is_q;

	is_q = (*s == '\'' || *s == '\"');
	if (*s == '\'') next = finds_noescape("\'", s + 1) + 1;
	else if (*s == '\"') next = finds_noescape("\"", s + 1) + 1;
	else next = finds_noescape("\'\")"IS_SPACE, s);
	if (is_q && next == ft_strlen_int(s))
		return (printf(ERROR_MSG"missing closing `%c'\n", *s), -1);
	//CDO: readline if next_q is LEN
	ft_lstadd_back(strs_ptr, ft_lstnew(ft_strdup(chop(s + is_q, next - 1 - is_q))));
	return (next + 1 * is_q);
}

//can fail -1
int	add_string(t_list **lst, char *s)
{
	t_list	*strs = NULL;
	char	*start;
	int		move;
	
	start = s;
	while (*s)
	{
		move = add_until(&strs, s);
		if (move == -1) return -1;
		s += move;
	}
	insert_token_into_lst(LITERAL, list_2_str(strs), lst, 0);
	return s - start;
}

void    unwrap_envvars(t_list *iter)
{
    t_dict_int_str_member   *m;
    int                     prev_type = NONE;

    while (iter)
    {
        m = _member(iter);
        if (m->key == LITERAL && !(prev_type == HEREDOCOP))
            m->value = handle_env(m->value);
        prev_type = m->key;
        iter = iter->next;
    }
}

// can fail -> NULL, removes empty strings
t_list  *unwrap_quotes(t_list *iter, t_list **unwraped)
{
    t_dict_int_str_member   *m;

    while (iter)
    {
        m = _member(iter);
        if (m->key == LITERAL && *(m->value))
        {
            char **split = ft_splitf(m->value, find_literal_end);
            while (*split != NULL)
                if (add_string(unwraped, *split++) == -1)
                    return (NULL);
        }
		else if (m->key == LITERAL) ;
        else
            insert_token_into_lst(m->key, m->value, unwraped, 0);
        iter = iter->next;
    }
    return *unwraped;
}

//can fail if ambigous redirect
//TODO should fail if matches fails
t_list  *unwrap_matches(t_list *iter, t_list **matched)
{
    t_dict_int_str_member	*m;
    t_list					*found;
    int						prev_type = NONE;
    
    while (iter)
    {
        m = _member(iter);
        if (m->key == LITERAL && prev_type != HEREDOCOP)
        {
            found = NULL;
            add_wildmatches(&found, m->value);
			if (IS_REDIR(prev_type) && ft_lstsize(found) > 1)
				return (printf(ERROR_MSG"%s: ambigous redirect\n", m->value), NULL);
			while (found)
            {
                insert_token_into_lst(LITERAL, found->content, matched, 0);
                found = found->next;
            }
        }
        else
            insert_token_into_lst(m->key, m->value, matched, 0);
        prev_type = m->key;
        iter = iter->next;
    }
    return *matched;
}

//can fail if no closing quotes or wildcard fails (ambigours redirect)
t_list  *unwrap(t_list *lexemes)
{
    t_list *unwraped = NULL;
    t_list *matched = NULL;

    unwrap_envvars(lexemes);
	if (unwrap_quotes(lexemes, &unwraped) == NULL)
        return NULL;
    if (unwrap_matches(unwraped, &matched) == NULL)
		return NULL;
    return matched;
}
