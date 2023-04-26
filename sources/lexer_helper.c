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

/* returns -1 if a malloc fails, otherwise length of lexeme */
int	insert_token_into_lst(enum TokenTypes type, char *value, t_list **lst)
{
	t_dict_int_str_member	*member;
	t_list					*new;

	member = t_dict_int_str_member_init(type, value);
	if (!member)
		return (-1);
	new = ft_lstnew(member);
	if (!new)
	{
		t_dict_int_str_member_free(member);
		return (-1);
	}
	ft_lstadd_back(lst, new);
	if (type == LPAREN || type == RPAREN || type == PIPE || type == REDIRLEFT || type == REDIRRIGHT || type == EQUAL)
		return (1);
	if (type == HEREDOC || type == APPEND || type == AND || type == OR)
		return (2);
	return (ft_strlen_int(value));
}

/* expansion, but no wildcards */
int	handle_double_quote(t_list **lst, char *s, int pos)
{
	char	*literal;
	int		insert_res;
	int		i;
	t_list	*word;

	word = NULL;
	i = 1;
	while (s[pos + i] && (s[pos + i] != '"' || !ft_chr_escaped(pos + i, s + pos)))
		i ++;
	literal = ft_calloc((i - 1), sizeof(*literal));
	if (!literal)
		return (-1);
	ft_strlcpy(literal, s + pos + 1, i);
	insert_res = insert_token_into_lst(LITERAL, literal, lst);
	free(literal);
	return (insert_res);
}

/* no expansion, no substitution, no escapes, we only and only stop at a second ' */
int	handle_single_quote(t_list **lst, char *s, int pos)
{
	char	*literal;
	int		insert_res;
	int		i;

	i = 1;
	while (s[pos + i] && s[pos + i] != '\'')
		i ++;
	literal = ft_calloc((i - 1), sizeof(*literal));
	if (!literal)
		return (-1);
	ft_strlcpy(literal, s + pos + 1, i);
	insert_res = insert_token_into_lst(LITERAL, literal, lst);
	free(literal);
	return (insert_res);
}

/* like double quote but stops at non literal chars and handles wildcards
 * important to remember that lol\ lel is one word ('lol lel')
 * */
int	handle_noquote(t_list **lst, char *s, int pos)
{
	(void) lst;
	(void) s;
	(void) pos;
	return (0);
}

/* returns -1 if a malloc fails, -2 if unknown char, otherwise length of lexeme */
int	handle_lexeme(t_list **lst, char *s, int pos)
{
	char	c1;
	char	c2;

	c1 = s[pos];
	c2 = s[pos + 1];
	if (c1 == '(')
		return (insert_token_into_lst(LPAREN, NULL, lst));
	if (c1 == ')')
		return (insert_token_into_lst(RPAREN, NULL, lst));
	if (c1 == '|' && c2 != '|')
		return (insert_token_into_lst(PIPE, NULL, lst));
	if (c1 == '<' && c2 != '<')
		return (insert_token_into_lst(REDIRLEFT, NULL, lst));
	if (c1 == '>' && c2 != '>')
		return (insert_token_into_lst(REDIRRIGHT, NULL, lst));
	if (c1 == '=')
		return (insert_token_into_lst(EQUAL, NULL, lst));
	if (c1 == '&')
		return (insert_token_into_lst(AND, NULL, lst));
	if (c1 == '|')
		return (insert_token_into_lst(OR, NULL, lst));
	if (c1 == '<')
		return (insert_token_into_lst(HEREDOC, NULL, lst));
	if (c1 == '>')
		return (insert_token_into_lst(APPEND, NULL, lst));
	if (ft_isspace(c1))
		return (1);
	if (c1 == '\'')
		return (handle_single_quote(lst, s, pos));
	return (-2);
}

void	del_dict_node(void *node)
{
	t_dict_int_str_member_free(node);
}

t_list	*tlst_error_exit(t_list **lst)
{
	ft_lstclear(lst, del_dict_node);
	return (NULL);
}

t_list	*scan_tokens(char *s)
{
	t_list	*res;
	int		i;
	int		start;
	int		advance_len;

	(void) start;
	//start = 0;
	i = 0;
	while (s[i])
	{
		advance_len = handle_lexeme(&res, s, i);
		if (advance_len == -1)
			return (tlst_error_exit(&res));
		i += advance_len;
	}
	res = NULL;
	return (res);
}
