/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	_type(t_list *lexeme)
{
	t_dict_int_str_member	*x;

	x = lexeme->content;
	return (x->key);
}

char	*_content(t_list *lexeme)
{
	t_dict_int_str_member	*x;

	x = lexeme->content;
	return (x->value);
}

char	**_content_ptr(t_list *lexeme)
{
	t_dict_int_str_member	*x;

	x = lexeme->content;
	return (&(x->value));
}

char	*_type_str(t_list *lexme)
{
	int	t;

	t = _type(lexme);
	if (t == LPAREN)
		return (ft_strdup("("));
	else if (t == RPAREN)
		return (ft_strdup(")"));
	else if (t == PIPE)
		return (ft_strdup("|"));
	else if (t == REDIR_L)
		return (ft_strdup("<"));
	else if (t == REDIR_R)
		return (ft_strdup(">"));
	else if (t == HEREDOC)
		return (ft_strdup("<<"));
	else if (t == APPEND)
		return (ft_strdup(">>"));
	else if (t == AND)
		return (ft_strdup("&&"));
	else if (t == OR)
		return (ft_strdup("||"));
	else if (t == LITERAL)
		return (ft_strdup(_content(lexme)));
	return (ft_strdup("interal error"));
}

t_dict_int_str_member	*_member(t_list *lexeme)
{
	return ((t_dict_int_str_member *)(lexeme->content));
}
