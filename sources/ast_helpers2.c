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

t_ast_node	*add_child(t_ast_node *parent, t_ast_node new)
{
	t_list		*lst_elem;
	t_ast_node	*new_node;

	lst_elem = ft_lstnew(NULL);
	new_node = gc_malloc(sizeof(t_ast_node));
	new_node->type = new.type;
	new_node->content = new.content;
	new_node->children = new.children;
	lst_elem->content = new_node;
	ft_lstadd_back(&(parent->children), lst_elem);
	return (new_node);
}

//REDIR left right append heredoc
int	is_redir(int t)
{
	return (t == REDIR_L || t == REDIR_R || t == APPEND || t == HEREDOC);
}
