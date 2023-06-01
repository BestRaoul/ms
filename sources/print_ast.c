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

void print_node(t_ast_node *ast, int depth)
{
	for (int i = 0; i < depth; ++i) {
		ft_printf("    ");
	}
	ft_printf("ASTnode: [%s", RED);
	print_type(ast->type);
	ft_printf("%s]\n", RESET);
	if (ast->content)
	{
		for (int i = 0; i < depth; ++i) {
			ft_printf("    ");
		}
		ft_printf("  content: `%s%s%s`\n", GREEN, ast->content, RESET);
	}
}

void print_ast(t_ast_node *ast, int depth)
{
	print_node(ast, depth);
	depth ++;
	for (int i = 0; i < ft_lstsize(ast->children); ++i) {
		print_ast(ft_lst_get(ast->children, i)->content, depth);
	}
}
