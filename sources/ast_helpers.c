/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"
#define ERROR_MSG "TODO: parser: "

static int	peek_type(t_list *lexeme)
{
	if (lexeme->next == NULL)
		return (NONE);
	return (_type(lexeme->next));
}

//assumption for parse_(arg, redir, heredoc, suffix)
//lexeme is not NULL
//type is correct

// lit nq, ', "
int	parse_arg(t_list *lexeme, t_ast_node *ast)
{
	add_child(ast, (t_ast_node){_type(lexeme), _content(lexeme), 0});
	*_content_ptr(lexeme) = NULL;
	return (1);
}

// '>' '>>' '<'
int	parse_redir(t_list *lexeme, t_ast_node *ast)
{
	int	peek;

	peek = peek_type(lexeme);
	if (peek != LITERAL)
		return (ft_dprintf(2, \
			ERROR_MSG"(0) filename expected after token `%s`\n",
				_type_str(lexeme)), -1);
	add_child(ast, (t_ast_node){_type(lexeme), _content(lexeme->next), 0});
	*_content_ptr(lexeme->next) = NULL;
	return (2);
}

// '<<'
int	parse_heredoc(t_list *lexeme, t_ast_node *ast)
{
	int	peek;

	peek = peek_type(lexeme);
	if (peek != LITERAL)
		return (ft_dprintf(2, ERROR_MSG"(1) delimiter expected\n"), -1);
	add_child(ast, (t_ast_node){HEREDOC, _content(lexeme->next), 0});
	*_content_ptr(lexeme->next) = NULL;
	return (2);
}

// '|' '&&' '||'
int	parse_suffix(t_list *lexeme, t_ast_node *ast)
{
	add_child(ast, (t_ast_node){_type(lexeme), 0, 0});
	return (1);
}
