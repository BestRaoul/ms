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

/* returns -1 if a MALLOC fails, otherwise length of lexeme */
int	insert_token_into_lst(enum TokenTypes type, char *value, t_list **lst, int advance_len)
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
	if (type == HEREDOCOP || type == APPEND || type == AND || type == OR)
		return (2);
	return (advance_len);
}

/* expansion, but no wildcards */
int	handle_double_quote(t_list **lst, char *s, int pos)
{
	char	*literal;
	int		insert_res;
	int		i;
	t_list	*word;

	/* handle empty string case */
	if (s[pos] == '"' && s[pos + 1] == '"')
		//return (2);
	{
		literal = ft_calloc(1, sizeof(*literal));
		if (!literal)
			return (-1);
		insert_res = insert_token_into_lst(LITERAL_DQ, literal, lst, 2);
		free(literal);
		return (insert_res);
	}
	word = NULL;
	i = 1;
	while (s[pos + i] && (s[pos + i] != '"' || ft_chr_escaped(pos + i, s + pos))) {
		if (!ft_lstadd_chr(s[pos + i], &word))
		{
			ft_lstclear(&word, ft_delnode);
			return (-1);
		}
		i++;
	}
	literal = ft_tlst_to_str(word);
	if (!literal)
	{
		ft_lstclear(&word, ft_delnode);
		return (-1);
	}
	insert_res = insert_token_into_lst(LITERAL_DQ, literal, lst, i + 1);
	free(literal);
	ft_lstclear(&word, ft_delnode);
	return (insert_res);
}

/* no expansion, no substitution, no escapes, we only and only stop at a second ' */
int	handle_single_quote(t_list **lst, char *s, int pos)
{
	char	*literal;
	int		insert_res;
	int		i;

	/* handle empty string case */
	if (s[pos] == '\'' && s[pos + 1] == '\'')
		//return (2);
	{
		literal = ft_calloc(1, sizeof(*literal));
		if (!literal)
			return (-1);
		insert_res = insert_token_into_lst(LITERAL_SQ, literal, lst, 2);
		free(literal);
		return (insert_res);
	}
	i = 1;
	while (s[pos + i] && s[pos + i] != '\'')
		i ++;
	literal = ft_calloc((i - 1), sizeof(*literal));
	if (!literal)
		return (-1);
	ft_strlcpy(literal, s + pos + 1, i);
	insert_res = insert_token_into_lst(LITERAL_SQ, literal, lst, i + 1);
	free(literal);
	return (insert_res);
}

/* function that tells if a char can be part of an unquoted literal */
int	valid_noquote_chr(char c)
{
	return (c != '(' && c != ')' && c != '|' && c != '<' && c != '>' /*&& c != '='*/ && !ft_isspace(c));
}

/* like double quote but stops at non literal chars and handles wildcards
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
		if (!ft_lstadd_chr(s[pos + i], &word))
		{
			ft_lstclear(&word, ft_delnode);
			return (-1);
		}
		i++;
	}
	literal = ft_tlst_to_str(word);
	if (!literal)
	{
		ft_lstclear(&word, ft_delnode);
		return (-1);
	}
	insert_res = insert_token_into_lst(LITERAL_NQ, literal, lst, i);
	free(literal);
	ft_lstclear(&word, ft_delnode);
	return (insert_res);
}

/* returns -1 if a MALLOC fails, -2 if unknown char, otherwise length to advance */
int	handle_lexeme(t_list **lst, char *s, int pos)
{
	char	c1;
	char	c2;

	c1 = s[pos];
	c2 = s[pos + 1];
	if (c1 == '(')
		return (insert_token_into_lst(LPAREN, NULL, lst, -1));
	else if (c1 == ')')
		return (insert_token_into_lst(RPAREN, NULL, lst, -1));
	else if (c1 == '|' && c2 != '|')
		return (insert_token_into_lst(PIPE, NULL, lst, -1));
	else if (c1 == '<' && c2 != '<')
		return (insert_token_into_lst(REDIRLEFT, NULL, lst, -1));
	else if (c1 == '>' && c2 != '>')
		return (insert_token_into_lst(REDIRRIGHT, NULL, lst, -1));
	//else if (c1 == '=')
		//return (insert_token_into_lst(EQUAL, NULL, lst, -1));
	else if (c1 == '&')
		return (insert_token_into_lst(AND, NULL, lst, -1));
	else if (c1 == '|')
		return (insert_token_into_lst(OR, NULL, lst, -1));
	else if (c1 == '<')
		return (insert_token_into_lst(HEREDOCOP, NULL, lst, -1));
	else if (c1 == '>')
		return (insert_token_into_lst(APPEND, NULL, lst, -1));
	else if (ft_isspace(c1))
		return (1);
	else if (c1 == '\'')
		return (handle_single_quote(lst, s, pos));
	else if (c1 == '"')
		return (handle_double_quote(lst, s, pos));
	else if(1) // literals probably cant start with something
		return (handle_noquote(lst, s, pos));
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
	res = NULL;
	i = 0;
	while (s && s[i])
	{
		advance_len = handle_lexeme(&res, s, i);
		//print_lexeme_tlist(res);
		if (advance_len < 0)
			return (tlst_error_exit(&res));
		i += advance_len;
	}
	return (res);
}

int	check_parenthesis(t_list *lexemes)
{
	int		open_parentheses;
	int		i;
	t_list	*tmp;
	int		current_key;

	open_parentheses = 0;
	i = 0;
	while (i < ft_lstsize(lexemes))
	{
		tmp = ft_lst_get(lexemes, i);
		if (!tmp)
			return (0);
		current_key = ((t_dict_int_str_member *)tmp->content)->key;
		if (current_key == LPAREN)
			open_parentheses ++;
		else if (current_key == RPAREN)

		i ++;
	}
	return (1);
}
