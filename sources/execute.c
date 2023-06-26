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

#define ERROR_MSG "ms: "

//ENS
//exit point -> never returns
void	execute_command(char **argv, t_list *_r, pid_t p_pid, t_parenthesis ps)
{
	t_ast_node	pll;
	int			status;
	char		*pathname;
	char		**my_argv;

	debug_prints_execute_command(argv, _r, p_pid);
	if (consume_redirs(_r) == -1)
		exit(errno);
	close_all_pipes(_r, 1);
	pll = (t_ast_node){PIPELINELIST, NULL, ps.children};
	if (!g_.is_sig && ps.type == PARENTHESIS)
		(execute(&pll), close_and_free_all(), exit(g_.status));
	else if (is_builtin(argv[0]))
	{
		status = exec_builtin(argv[0], argv);
		(close_and_free_all(), exit(status));
	}
	my_argv = realloc_strarr_no_gc(argv);
	(garbage_collector(FREE_ALL, 0), close(g_.dup_stdin), close(g_.dup_stdout));
	pathname = where_bin(my_argv[0]);
	if (!g_.is_sig && pathname != NULL)
		execve(pathname, my_argv, g_.env);
	if (!g_.is_sig)
		ft_dprintf(2, "%s: command not found\n", my_argv[0]);
	(reown(my_argv), close_and_free_all(), exit(127));
}

//ENS
//crashes if sc fail
//always non-null return value
pid_t	*init_subshells(char ***argvs, t_parenthesis *parens, int p_count)
{
	pid_t	*pids;
	pid_t	parent;
	int		i;

	pids = ft_calloc(p_count + 1, sizeof(pid_t));
	parent = getpid();
	i = 0;
	while (i < p_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			crash();
		if (pids[i] == 0)
			execute_command(argvs[i], g_.redirs[i], parent, parens[i]);
		i++;
	}
	return (pids);
}

//ENS
int	do_solo_exec_builtin(char **argv)
{
	int	status;

	if (consume_redirs(g_.redirs[0]) == -1)
		return (errno);
	status = exec_builtin(argv[0], argv);
	close_all_pipes(NULL, 1);
	if (dup2(g_.dup_stdin, STDIN_FILENO) == -1
		|| dup2(g_.dup_stdin, STDOUT_FILENO) == -1)
		crash();
	return (status);
}

//ENS
static int	execute_pipeline(t_ast_node *pipeline)
{
	char			***argvs;
	t_parenthesis	*parens;
	pid_t			*pids;
	int				pipe_count;

	pipe_count = count_child_pipes(pipeline) + 1;
	argvs = alloc_argvs(pipeline, pipe_count);
	g_.redirs = ft_calloc(pipe_count + 1, sizeof(t_list *));
	parens = ft_calloc(pipe_count + 1, sizeof(t_parenthesis));
	populate_execution_data(argvs, parens, pipeline);
	if (pipe_count == 1 && is_builtin(argvs[0][0]))
		return (do_solo_exec_builtin(argvs[0]));
	pids = init_subshells(argvs, parens, pipe_count);
	close_all_pipes(NULL, 1);
	pipe_count = -42;
	while (*pids)
	{
		waitpid(*pids, &pipe_count, 0);
		pids++;
	}
	return (pipe_count);
}

//ENS
void	execute(t_ast_node *pipeline_list)
{
	t_ast_node	*child;
	t_ast_node	*next;
	int			child_i;
	int			status;

	child_i = 0;
	child = get_child(pipeline_list, child_i++);
	status = 1;
	while (child != NULL)
	{
		if (status == 1)
		{
			status = execute_pipeline(child);
			set_g_status(status);
		}
		else
			status = -42;
		next = get_child(pipeline_list, child_i++);
		if (next == NULL)
			break ;
		status = (next->type == AND) * (status == 0)
			+ (next->type == OR) * (status != 0);
		child = get_child(pipeline_list, child_i++);
	}
}
