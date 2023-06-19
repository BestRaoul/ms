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

void	spaces(int s)
{
	int	i = 0;
	while (i < s)
	{
		write(1, " ", 1);
		i++;
	}
}

void	print_node(t_ast_node *ast, int depth)
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
		write(2, "print_ast: NULL\n", 16);
		return ;}
	print_node(ast, depth);
	depth ++;
	for (int i = 0; i < ft_lstsize(ast->children); ++i) {
		print_ast(ft_lst_get(ast->children, i)->content, depth);
	}
}
