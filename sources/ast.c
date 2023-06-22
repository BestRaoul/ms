/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ms.h"

#define DEBUG_AST 0
#define EMSG "TODO:ast parser: "

//for self reference
static int	parse_pipelinelist(t_list **lexeme_ptr, t_ast_node *ast, int init);

// lit, redir, <<, |, '(' => pipeline_list, [')', '&&', '||'] => exit
static int	parse_pipeline(t_list **lexme_ptr, t_ast_node *ast)
{
	t_ast_node	*pipeline;
	int			ac;
	int			rc;
	int			pc;
	int			t;
	int			m;

	pipeline = add_child(ast, (t_ast_node){PIPELINE, 0, 0});
	(ac = 0, rc = 0, pc = 0);
	while (*lexme_ptr != NULL)
	{
		t = _type(*lexme_ptr);
		if ((t == LITERAL) && (pc == 0))
			(m = parse_arg(*lexme_ptr, pipeline), ac++);
		else if (t == REDIRLEFT || t == REDIRRIGHT || t == APPEND)
			(m = parse_redir(*lexme_ptr, pipeline), rc++);
		else if (t == HEREDOC)
			(m = parse_heredoc(*lexme_ptr, pipeline), rc++);
		else if (t == PIPE && (ac + rc + pc > 0))
			(m = parse_suffix(*lexme_ptr, pipeline), ac = 0, rc = 0, pc = 0);
		else if (t == LPAREN && (ac == 0 && pc == 0))
		{
			*lexme_ptr = (*lexme_ptr)->next;
			m = parse_pipelinelist(lexme_ptr, pipeline, 0);
			pc++;
		}
		else if (t == AND || t == OR || t == RPAREN)
			break ;
		else
		{
			if (ac + rc + pc == 0)
				break ;
			return (ft_dprintf(2, EMSG"(2) error near unexpected `%s' token\n",
					_type_str(*lexme_ptr)), -1);
		}
		if (m == -1)
			return (-1);
		*lexme_ptr = (*lexme_ptr)->next;
		if (m == 2)
			*lexme_ptr = (*lexme_ptr)->next;
	}
	if (ac + rc + pc == 0)
		return (ft_dprintf(2, EMSG"(3) missing tokens\n"), -1);
	return (0);
}

// pipeline, `&&' or `||'
static int	parse_pipelinelist(t_list **lexme_ptr, t_ast_node *ast, int init)
{
	t_ast_node	*pipeline_list;
	int			t;

	if (init)
		pipeline_list = ast;
	else
		pipeline_list = add_child(ast, (t_ast_node){PIPELINELIST, 0, 0});
	if (*lexme_ptr == NULL)
		return (ft_dprintf(2, EMSG"(4) missing tokens\n"), -1);
	while (*lexme_ptr != NULL)
	{
		if (parse_pipeline(lexme_ptr, pipeline_list) == -1)
			return (-1);
		if (*lexme_ptr == NULL)
		{
			if (init)
				return (0);
			return (ft_dprintf(2, EMSG"(5) missing closing `)' token\n"),
				-1);
		}
		t = _type(*lexme_ptr);
		if (t == AND || t == OR)
		{
			if ((*lexme_ptr)->next == NULL)
				return (ft_dprintf(2, EMSG"(6) missing token after `%s' token\n",
					_type_str(*lexme_ptr)), -1);
			parse_suffix(*lexme_ptr, pipeline_list);
		}
		else if (t == RPAREN && !init)
			return (0);
		else
			return (ft_dprintf(2, EMSG"(7) syntax error near unxepected `%s' token\n",
				_type_str(*lexme_ptr)), -1);
		*lexme_ptr = (*lexme_ptr)->next;
	}
	return (0);
}

t_ast_node	*parse(t_list *lexemes)
{
	t_ast_node	*ast;
	t_list		**lexme_ptr;
	t_list		*lexme;

	ast = MALLOC(sizeof(t_ast_node));
	ast->children = NULL;
	ast->content = NULL;
	ast->type = PIPELINELIST;
	lexme_ptr = &lexemes;
	if (parse_pipelinelist(lexme_ptr, ast, 1) == -1)
		return (NULL);
	lexme = *lexme_ptr;
	if (lexme && lexme->next)
		return (ft_dprintf(2, EMSG"(8) syntax error near unexpected token `%s'\n",
			_type_str(lexme->next)), NULL);
	if (g_.print_ast)
	{
		print_ast(ast, 0);
		g_.print_ast = 0;
	}
	return (ast);
}
