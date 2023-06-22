/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unwrap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define EMSG "ms: "

char	*list_2_str(t_list *lst)
{
	int		total_len;
	t_list	*i;
	char	*str;
	int		j;

	total_len = 0;
	i = lst;
	while (i)
	{
		total_len += len(lst->content);
		i = i->next;
	}
	str = MALLOC(total_len + 1);
	j = 0;
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
	char	**res;
	int		i;

	res = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	i = 0;
	while (lst)
	{
		res[i++] = lst->content;
		lst->content = NULL;
		lst = lst->next;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_splitf(char *s, int (*_next)(char *))
{
	t_list	*strs;
	int		next_end;

	strs = NULL;
	while (*s)
	{
		next_end = _next(s);
		if (next_end > 0)
			ft_lstadd_back(&strs, ft_lstnew(chop(s, next_end - 1)));
		s += next_end;
		if (!*s)
			break ;
		s++;
	}
	return (list_2_strr(strs));
}

//can fail, no closing quote -1
//CDO: readline if next_q is LEN
int	add_until(t_list **strs_ptr, char *s)
{
	int		next;
	int		is_q;

	is_q = (*s == '\'' || *s == '\"');
	if (*s == '\'')
		next = finds_noescape("\'", s + 1) + 1;
	else if (*s == '\"')
		next = finds_noescape("\"", s + 1) + 1;
	else
		next = finds_noescape("\'\")"IS_SPACE, s);
	if (is_q && next == len(s))
		return (printf(EMSG"missing closing `%c'\n", *s), -1);
	ft_lstadd_back(strs_ptr, ft_lstnew(ft_strdup(
				chop(s + is_q, next - 1 - is_q))));
	return (next + 1 * is_q);
}

//can fail -1
int	add_string(t_list **lst, char *s)
{
	t_list	*strs;
	char	*start;
	int		move;

	strs = NULL;
	start = s;
	while (*s)
	{
		move = add_until(&strs, s);
		if (move == -1)
			return (-1);
		s += move;
	}
	insert_token_into_lst(LITERAL, list_2_str(strs), lst, 0);
	return (s - start);
}
