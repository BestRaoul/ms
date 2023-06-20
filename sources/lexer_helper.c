/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"
//We do not free here as it is cheaper to keep it for later
// and FREE_ALL with the garbage_collector

/* cannot fail
 returns length of lexeme */
int	insert_token_into_lst(enum TokenTypes type, char *value, t_list **lst, int advance_len)
{
	t_dict_int_str_member	*member;
	t_list					*new;

	member = t_dict_int_str_member_init(type, value);
	new = ft_lstnew(member);
	ft_lstadd_back(lst, new);
	return (advance_len);
}

int min(int x, int y)
{
	if (x < y)
		return x;
	return y;
}

char *list_2_str(t_list *lst)
{
	int	total_len = 0;
	t_list *i = lst;
	while (i)
	{
		total_len += len(lst->content);
		i = i->next;
	}
	char *str = MALLOC(total_len + 1);
	int	j = 0;
	i = lst;
	while (i)
	{
		ft_strlcpy(&(str[j]), i->content, len(i->content) + 1);
		j += len(i->content);
		i = i->next;
	}
	return (str);
}

//moves from one quote to the next + 1
//from ->'...'X<- to
int	add_quoted(t_list **strs_ptr, char **s_ptr)
{
	char 	*s;
	char	match;
	char	temp;
	int		next_q;
	int 	_l;

	s = *s_ptr;
	match = *s; //' or "
	s += 1;
	_l = len(s);
	next_q = find_noescape(match, s);
	//readline if next_q is LEN
	temp = s[next_q];
	s[next_q] = 0;
	if (match == '\'')
		ft_lstadd_back(strs_ptr, ft_lstnew(ft_strdup(s)));
	else
		ft_lstadd_back(strs_ptr, ft_lstnew(handle_env(s)));
	if (next_q != _l)
		s[next_q] = temp;
	*s_ptr += next_q + 2;
	return (next_q + 2);
}

int	add_unquoted(t_list **strs_ptr, char **s_ptr)
{
	char	*s;
	char	temp;
	int		next_q;
	int		next_s;

	s = *s_ptr;
	next_q = min(find_noescape_len('\'', s), find_noescape_len('\"', s));
	next_s = findf_noescape_len(ft_isspace, s);
	if (next_s <= next_q)
	{
		s[next_s] = 0;
		ft_lstadd_back(strs_ptr, ft_lstnew(handle_env(s)));
		if (next_s != next_q)
			s[next_s] = ' ';
		*s_ptr += next_s;
		return (-1);
	}
	temp = s[next_q];
	s[next_q] = 0;
	ft_lstadd_back(strs_ptr, ft_lstnew(handle_env(s)));
	s[next_q] = temp;
	*s_ptr += next_q;
	return (next_q);
}

/* can fail if does not find matching*/
int	handle_string(t_list **lst, char *s, int pos)
{
	t_list	*strs = NULL;
	char	*start;

	s += pos;
	start = s;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
			add_quoted(&strs, &s);
		else if (add_unquoted(&strs, &s) == -1)
			break;
	}
	return insert_token_into_lst(LITERAL, list_2_str(strs), lst, (s - start));
}

/* can fail, if quotes are not closed => returns -1
else returns length to advance */
int	handle_lexeme(t_list **lst, char *s, int pos)
{
	char	c1;
	char	c2;

	c1 = s[pos];
	c2 = s[pos + 1];
	if (c1 == '(')
		return (insert_token_into_lst(LPAREN, NULL, lst, 1));
	else if (c1 == ')')
		return (insert_token_into_lst(RPAREN, NULL, lst, 1));
	else if (c1 == '|' && c2 != '|')
		return (insert_token_into_lst(PIPE, NULL, lst, 1));
	else if (c1 == '<' && c2 != '<')
		return (insert_token_into_lst(REDIRLEFT, NULL, lst, 1));
	else if (c1 == '>' && c2 != '>')
		return (insert_token_into_lst(REDIRRIGHT, NULL, lst, 1));
	else if (c1 == '&')
		return (insert_token_into_lst(AND, NULL, lst, 2));
	else if (c1 == '|')
		return (insert_token_into_lst(OR, NULL, lst, 2));
	else if (c1 == '<')
		return (insert_token_into_lst(HEREDOCOP, NULL, lst, 2));
	else if (c1 == '>')
		return (insert_token_into_lst(APPEND, NULL, lst, 2));
	else if (ft_isspace(c1))
		return (1);
	else if (c1 == '\'' || c1 == '\"' || 1)
		return (handle_string(lst, s, pos));
}

t_list	*lex(char *s)
{
	t_list	*res;
	int		i;
	int		advance_len;
	t_list	*first;

	res = NULL;
	i = 0;
	while (s && s[i])
	{
		advance_len = handle_lexeme(&res, s, i);
		if (advance_len < 0)
			return (NULL);
		i += advance_len;
	}
	first = ft_lst_get(res, 0);
	if (first && ((t_dict_int_str_member * )(first->content))->value && ft_strequal( ((t_dict_int_str_member * )(first->content))->value, "ast"))
	{
		g.print_ast = 1;
		ft_lst_rm(&res, 0);
	}
	return (res);
}
