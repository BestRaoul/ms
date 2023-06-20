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

/* can fail if no closing "
 expansion, but no wildcards */
int	handle_double_quote(t_list **lst, char *s, int pos)
{
	char	*literal;
	int		insert_res;
	int		i;
	t_list	*word;

	if (!in('"', s + pos + 1))
	{
		ft_printf("Closing `\"' expected!\n");
		return (-1);
	}
	/* handle empty string case */
	if (s[pos] == '"' && s[pos + 1] == '"')
		return (insert_token_into_lst(LITERAL_DQ, "", lst, 2));
	word = NULL;
	i = 1;
	while (s[pos + i] && (s[pos + i] != '"' || ft_chr_escaped(pos + i, s + pos))) {
		ft_lstadd_chr(s[pos + i], &word);
		i++;
	}
	literal = ft_tlst_to_str(word);
	insert_res = insert_token_into_lst(LITERAL_DQ, literal, lst, i + 1);
	return (insert_res);
//	FREE(literal);
//	ft_lstclear(&word, ft_delnode);
}

/* can fail if no closing '
 no expansion, no substitution, no escapes, we only and only stop at a second ' */
int	handle_single_quote(t_list **lst, char *s, int pos)
{
	char	*literal;
	int		insert_res;
	int		i;

	if (!in('\'', s + pos + 1))
	{
		ft_printf("Closing `'' expected!\n");
		return (-1);
	}
	/* handle empty string case */
	if (s[pos] == '\'' && s[pos + 1] == '\'')
		return (insert_token_into_lst(LITERAL_SQ, "", lst, 2));
	i = 1;
	while (s[pos + i] && s[pos + i] != '\'')
		i ++;
	literal = ft_calloc((i - 1), sizeof(*literal));
	ft_strlcpy(literal, s + pos + 1, i);
	insert_res = insert_token_into_lst(LITERAL_SQ, literal, lst, i + 1);
	return (insert_res);
//	FREE(literal);
}

/* function that tells if a char can be part of an unquoted literal */
int	valid_noquote_chr(char c)
{
	return (c != '(' && c != ')' && c != '|' && c != '<' && c != '>' && !ft_isspace(c));
}

/* cannot fail
 like double quote but stops at non literal chars and handles wildcards
 * important to remember that lol\ lel is one word ('lol lel')
 * variable substitution happens prior to wildcard matching
 * */
int	handle_noquote(t_list **lst, char *s, int pos)
{
	char	*literal;
	int		insert_res;
	int		i;
	t_list	*word;

	word = NULL;
	i = 0;
	while (s[pos + i] && (valid_noquote_chr(s[pos + i]) || ft_chr_escaped(pos + i, s + pos)))
	{
		ft_lstadd_chr(s[pos + i], &word);
		i++;
	}
	literal = ft_tlst_to_str(word);
	insert_res = insert_token_into_lst(LITERAL_NQ, literal, lst, i);
	return (insert_res);
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
	else if (c1 == '\'')
		return (handle_single_quote(lst, s, pos));
	else if (c1 == '"')
		return (handle_double_quote(lst, s, pos));
	else // literals probably cant start with something
		return (handle_noquote(lst, s, pos));
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
