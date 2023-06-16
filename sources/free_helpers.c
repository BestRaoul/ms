/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <pkondrac@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by pkondrac          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	free_ast(t_ast_node *ast)
{
	int	i;

	if (!ast)
		return ;
	i = 0;
	while (i < ft_lstsize(ast->children))
	{
		free_ast(ft_lst_get(ast->children, i)->content);
		i ++;
	}
	if (ast->content)
		FREE(ast->content);
	if (ast->children)
		FREE(ast->children);
	FREE(ast);
	ast = NULL;
}

void    free_lexeme_node(void *node)
{
	t_dict_int_str_member_free(node);
	//FREE(node);
}
