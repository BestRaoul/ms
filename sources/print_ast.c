/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

static void	spaces(int s)
{
	int	i = 0;
	while (i < s)
	{
		if (write(1, " ", 1)) {}
		i++;
	}
}

static int	print_type2(int type)
{
	int	t;

	if (type == LITERAL)
		ft_printf("literal");
	if (type == PIPELINE)
		ft_printf("pipeline");
	if (type == PIPELINELIST)
		ft_printf("pipeline lst");
	if (type == HEREDOC)
		ft_printf("heredoc");
	t = type;
	return (t == LITERAL
		|| t == PIPELINE || t == PIPELINELIST || t == HEREDOC);
}

static void	print_type(int type)
{
	ft_printf("%s", RED);
	if (type == LPAREN)
		ft_printf("(");
	else if (type == RPAREN)
		ft_printf(")");
	else if (type == PIPE)
		ft_printf("|");
	else if (type == REDIRLEFT)
		ft_printf("<");
	else if (type == REDIRRIGHT)
		ft_printf(">");
	else if (type == HEREDOCOP)
		ft_printf("<<");
	else if (type == APPEND)
		ft_printf(">>");
	else if (type == AND)
		ft_printf("&&");
	else if (type == OR)
		ft_printf("||");
	else if (!print_type2(type))
		ft_printf("BIG ERROR");
	ft_printf("%s", RESET);
}

static void	print_node(t_ast_node *ast, int depth)
{
	spaces(4 * depth);
	ft_printf("ASTnode: [");
	print_type(ast->type);
	ft_printf("]\n");
	if (ast->content)
	{
		spaces(4 * depth);
		ft_printf("  content: `%s%s%s`\n", GREEN, ast->content, RESET);
	}
}

void	print_ast(t_ast_node *ast, int depth)
{
	if (!ast) {
		if (write(1, "print_ast: NULL\n", 16)) {}
		return ;}
	print_node(ast, depth);
	depth ++;
	for (int i = 0; i < ft_lstsize(ast->children); ++i) {
		print_ast(ft_lst_get(ast->children, i)->content, depth);
	}
}
