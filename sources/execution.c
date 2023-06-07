/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <pkondrac@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by pkondrac          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define IS_LITERAL(x) (x == LITERAL_NQ || x == LITERAL_SQ || x == LITERAL_DQ)
#define IS_REDIR(x) (x == REDIRLEFT || x == REDIRRIGHT || x == APPEND || x == HEREDOCOP)

// https://tldp.org/LDP/abs/html/io-redirection.html

t_ast_node	*get_child(t_ast_node	*node, int i)
{
	t_list	*temp = ft_lst_get(node->children, i++);
	if (temp == NULL) return (NULL);
	return (temp->content);
}

int	count_child_pipes(t_ast_node *ast)
{
	int	i = 0;
	int	c = 0;

	t_ast_node	*child = get_child(ast, i++);
	while (child != NULL)
	{
		c += child->type == PIPE;
		child = get_child(ast, i++);
	}
	return (c);
}

char	***alloc_argvs(t_ast_node *ast)
{
	int	i = 0;
	int	j = 0;
	t_ast_node	*child = get_child(ast, i++);
//	printf("argv's: %d\n", count_child_pipes(ast) + 1);
	char ***argvs = calloc(count_child_pipes(ast) + 1 + 1, sizeof(char **)); //nc
	int literal_c = 0;
	while (child != NULL)
	{
		literal_c += (child->type == LITERAL_NQ || child->type == LITERAL_SQ || child->type == LITERAL_DQ);
		if (child->type == PIPE)
		{
//			printf("(%d)-th argv: %d\n", j, literal_c + 1);
			argvs[j++] = calloc(literal_c + 1, sizeof(char *)); //nc
			literal_c = 0;
		}
		child = get_child(ast, i++);
	}
//	printf("(%d)-th argv: %d\n", j, literal_c + 1);
	argvs[j++] = calloc(literal_c + 1, sizeof(char *));
	argvs[j] = NULL;
	return (argvs);
}

void	print_argvs(char ***argvs, int pipe_i)
{
	for (int k=0; k<=pipe_i; k++)
	{
		printf("argv: [");
		int l=0;
		char **_argv = argvs[k];
		while (_argv[l] != NULL)
			printf("%s, ", _argv[l++]);
		printf("\b\b] argc: %d\n", l);
	}
}

void	ms_execute(t_ast_node *pipeline)
{
	int	i = 0;
	t_ast_node	*child = get_child(pipeline, i++);
	char	***argvs = alloc_argvs(pipeline);
	int	pipe_i = 0;
	int arg_i = 0;

	while (child != NULL)
	{
		/* --plan--
		//LITERAL -done
		//REDIR
			//handle redir -> switch
		//PIPE
			//j=0; argvs++; redirect both out and in
		//PIPELINE
			//-r ms_exec
		//AND,OR ??
			//'&&'/'||' found = inside parenthesis
		*/
		
		
		if (IS_LITERAL(child->type))
			(argvs[pipe_i])[arg_i++] = ft_strdup(child->content); //nc
		else if (IS_REDIR(child->type))
			printf("redir\n");
		else if (child->type == PIPE)
		{ pipe_i++; arg_i = 0; }
		else if (child->type == PIPELINE)
			ms_execute(child); // (if fail =>return -1;)
		else
			printf("BIG ERROR");
		
		child = get_child(pipeline, i++);
	}
	print_argvs(argvs, pipe_i);
	frees2(1, 1, argvs);
	return ;
}

//int	execve(path, argv, env);
/* fork => execve example
int	launch_sub(char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		return execve(argv[0], argv, NULL);
	else
		return 0;
}
*/

/* all token types you can find in a proper ast execute-ready tree
PIPE, // new argv
REDIRLEFT, // redirect
REDIRRIGHT, //redirect
HEREDOCOP, //redirect (but weirder, use static string for testing)
APPEND, >> //redirect but different
AND, //after of pipeline
OR, //after pipeline
LITERAL_NQ, //arg
LITERAL_SQ, //arg
LITERAL_DQ, //arg
PIPELINELIST,
PIPELINE, //inside
*/


