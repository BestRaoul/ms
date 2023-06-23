/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <pkondrac@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by pkondrac          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG "TODO: "

//ENS
t_ast_node	*get_child(t_ast_node	*node, int i)
{
	t_list	*temp;

	temp = ft_lst_get(node->children, i);
	if (temp == NULL)
		return (NULL);
	return (temp->content);
}

//ENS
t_redir	*get_redir(t_list	*redir, int i)
{
	t_list	*temp;

	temp = ft_lst_get(redir, i);
	if (temp == NULL)
		return (NULL);
	return (temp->content);
}

//ENS
t_list	*alloc_redir(int type, char *val)
{
	t_redir	*redir;
	t_list	*_redir;

	if (val == NULL)
		return (NULL);
	redir = gc_malloc(sizeof(t_redir));
	redir->type = type;
	redir->val = val;
	_redir = ft_lstnew(redir);
	return (_redir);
}

//ENS
char	***alloc_argvs(t_ast_node *ast, int pipe_count)
{
	char		***argvs;
	t_ast_node	*child;
	int			literal_c;
	int			i;
	int			j;

	i = 0;
	child = get_child(ast, i++);
	argvs = ft_calloc(pipe_count + 1, sizeof(char **));
	literal_c = 0;
	j = 0;
	while (child != NULL)
	{
		literal_c += (child->type == LITERAL);
		if (child->type == PIPE)
		{
			argvs[j++] = ft_calloc(literal_c + 1, sizeof(char *));
			literal_c = 0;
		}
		child = get_child(ast, i++);
	}
	argvs[j++] = ft_calloc(literal_c + 1, sizeof(char *));
	argvs[j] = NULL;
	return (argvs);
}
