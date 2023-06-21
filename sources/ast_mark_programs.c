/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_mark_programs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:32 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 12:42:36 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	ast_mark_cmd(t_ast_node *ast, int is_first)
{
	t_list		*child;
	int			ret;

	ret = 1;
	if (is_first && ast->type == LITERAL)
		ast->node_is_cmd = 1;

	for (int i = 0; i < ft_lstsize(ast->children); ++i) {
		child = ft_lst_get(ast->children, i);
		if (!child)
			return (0);
		ret = ft_min_int(ast_mark_cmd(child->content, i == 0), 1);
	}
	return (ret);
}
