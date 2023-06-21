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

#define ERROR_MSG SHELL_MSG"lex: "

// cannot fail returns i
int	insert_token_into_lst(enum TokenTypes type, char *value, t_list **lst, int i)
{
	t_dict_int_str_member	*member;
	t_list					*new;

	member = t_dict_int_str_member_init(type, value);
	new = ft_lstnew(member);
	ft_lstadd_back(lst, new);
	return (i);
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

int find_literal_end(char *s)
{

	return finds_ne_nq(")"IS_SPACE, s);
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
	if (is_q && next == len(s))
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

// can fail -1
int	handle_string(t_list **lst, char *s, int pos)
{
	char	**split;
	char	*s2;
	int		end;
	int		move;	
	
	s += pos;
	end = find_literal_end(s);
	s2 = handle_env_until(s, end);
	split = ft_splitf(s2, find_literal_end);
	while (*split != NULL)
	{
		move = add_string(lst, *split++);
		if (move == -1)
			return (-1);
		s += move;
	}
	return (end);
}

//can fail -1
int	handle_heredoc(t_list **lst, char *s, int pos)
{
	char	*start;
	char	*s2;
	int		end;

	insert_token_into_lst(HEREDOCOP, NULL, lst, 2);
	start = s;
	s += pos + 2;
	while (ft_isspace(*s))
		s++;
	end = find_literal_end(s);
	s2 = chop(s, end - 1);
	if (add_string(lst, s2) == -1)
		return -1;
	s += end;
	return (s - start);
}

// can fail -1, no closing quote
// else returns length to advance
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
		return (handle_heredoc(lst, s, pos));
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
