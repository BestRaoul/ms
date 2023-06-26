/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <pkondrac@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by pkondrac          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG "ms: "

typedef struct s_ped {
	int	arg_i;
	int	pip_i;
	int	cld_i;
	int	pipe[2];
}	t_ped;

static void	manage_pipe(t_ped *d, t_parenthesis *parens)
{
	if (pipe(d->pipe) == -1)
		crash();
	ft_lstadd_back(&(g_.redirs[d->pip_i]),
		alloc_redir(PIPE_OUT, ft_itoa(d->pipe[1])));
	d->arg_i = 0;
	parens[++d->pip_i] = (t_parenthesis){NONE, NULL};
	ft_lstadd_back(&(g_.redirs[d->pip_i]),
		alloc_redir(PIPE_IN, ft_itoa(d->pipe[0])));
}

//ENS sc
void	populate_execution_data(char ***argvs, t_parenthesis *ps, t_an *pl)
{
	t_ast_node	*child;
	t_ped		d;

	d = (t_ped){0, 0, 0, {-1, -1}};
	child = get_child(pl, d.cld_i++);
	while (child != NULL)
	{	
		if (child->type == LITERAL)
			(argvs[d.pip_i])[d.arg_i++] = child->content;
		else if (child->type == HEREDOC)
			ft_lstadd_back(&g_.redirs[d.pip_i],
				alloc_redir(HEREDOC, ft_itoa(heredoc_handler(child->content))));
		else if (is_redir(child->type))
			ft_lstadd_back(&g_.redirs[d.pip_i],
				alloc_redir(child->type, child->content));
		else if (child->type == PIPE)
			manage_pipe(&d, ps);
		else if (child->type == PIPELINELIST)
			ps[d.pip_i] = (t_parenthesis){PARENTHESIS, child->children};
		else
			(ft_dprintf(2, "pipeline: BIG ERROR\n"), exit(127));
		child = get_child(pl, d.cld_i++);
	}
}

//ENS
int	count_child_pipes(t_ast_node *ast)
{
	t_ast_node	*child;
	int			i;
	int			c;

	i = 0;
	c = 0;
	child = get_child(ast, i++);
	while (child != NULL)
	{
		c += child->type == PIPE;
		child = get_child(ast, i++);
	}
	return (c);
}

//ENS
int	heredoc_handler(char *delimiter)
{
	int		previous_in;
	char	*input;
	int		_pipe[2];

	previous_in = dup(STDIN_FILENO);
	if (previous_in == -1
		|| dup2(g_.dup_stdin, STDIN_FILENO) == -1 || pipe(_pipe) == -1)
		crash();
	input = readline("|> ");
	while (input != NULL && ft_strncmp(input, delimiter, len(input)) != 0)
	{
		if (write(_pipe[1], input, ft_strlen(input)) == -1
			|| write(_pipe[1], "\n", 1) == -1)
			crash();
		free(input);
		input = readline("|> ");
	}
	if (input == NULL)
		ft_dprintf(2, ERROR_MSG"warning: "
			"here-document delimited by end-of-file (wanted `%s')\n", delimiter);
	free(input);
	if (close(_pipe[1]) == -1
		|| dup2(previous_in, STDIN_FILENO) == -1)
		crash();
	return (_pipe[0]);
}
