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

void print_ast(t_ast_node *ast, int depth)
{
	for (int i = 0; i < depth; ++i) {
		ft_printf("    ");
	}
	ft_printf("ASTnode: [%d]\n", ast->type);
	if (ast->content)
	{
		for (int i = 0; i < depth; ++i) {
			ft_printf("    ");
		}
		ft_printf("  content: `%s`\n", ast->content);
	}
	depth ++;
	for (int i = 0; i < ft_lstsize(ast->children); ++i) {
		print_ast(ft_lst_get(ast->children, i)->content, depth);
	}
}
