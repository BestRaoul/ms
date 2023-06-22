/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG "ms: lex: "

// cannot fail returns i
int	insert_token_into_lst(enum TokenTypes t, char *value, t_list **lst, int i)
{
	t_dict_int_str_member	*member;
	t_list					*new;

	member = t_dict_int_str_member_init(t, value);
	new = ft_lstnew(member);
	ft_lstadd_back(lst, new);
	return (i);
}

int	find_literal_end(char *s)
{
	return (finds_ne_nq(")"IS_SPACE, s));
}

int	handle_string(t_list **lst, char *s, int pos)
{
	int		end;

	s += pos;
	end = find_literal_end(s);
	insert_token_into_lst(LITERAL, chop(s, end - 1), lst, 0);
	return (end);
}

// cannot fail, returns length to advance
int	handle_lexeme(t_list **lst, char *s, int pos)
{
	char	c1;
	char	c2;

	c1 = s[pos];
	c2 = s[pos + 1];
	if (c1 == '(' || c1 == ')')
		return (insert_token_into_lst(LPAREN * (c1 == '(')
				+ RPAREN * (c1 == ')'), NULL, lst, 1));
	else if (c1 == '|' && c2 != '|')
		return (insert_token_into_lst(PIPE, NULL, lst, 1));
	else if (c1 == '<' && c2 != '<')
		return (insert_token_into_lst(REDIRLEFT, NULL, lst, 1));
	else if (c1 == '>' && c2 != '>')
		return (insert_token_into_lst(REDIRRIGHT, NULL, lst, 1));
	else if (c1 == '&' || c1 == '|')
		return (insert_token_into_lst(AND * (c1 == '&')
				+ OR * (c1 == '|'), NULL, lst, 2));
	else if (c1 == '<' || c1 == '>')
		return (insert_token_into_lst(HEREDOC * (c1 == '<')
				+ APPEND * (c1 == '>'), NULL, lst, 2));
	else if (ft_isspace(c1))
		return (1);
	else
		return (handle_string(lst, s, pos));
}

t_list	*lex(char *s)
{
	t_list	*res;
	int		i;
	t_list	*first;

	res = NULL;
	i = 0;
	while (s && s[i])
		i += handle_lexeme(&res, s, i);
	first = ft_lst_get(res, 0);
	if (first && ((t_dict_int_str_member *)(first->content))->value
		&& ft_strequal(((t_dict_int_str_member *)(first->content))->value,
			"ast"))
	{
		g_.print_ast = 1;
		ft_lst_rm(&res, 0);
	}
	return (res);
}
