/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <pkondrac@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by pkondrac          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG "TODO: "

static char	*_type_2_str(int t)
{
	if (t == LPAREN)
		return (ft_strdup("("));
	else if (t == RPAREN)
		return (ft_strdup(")"));
	else if (t == PIPE)
		return (ft_strdup("|"));
	else if (t == REDIR_L)
		return (ft_strdup("<"));
	else if (t == REDIR_R)
		return (ft_strdup(">"));
	else if (t == HEREDOC)
		return (ft_strdup("<<"));
	else if (t == APPEND)
		return (ft_strdup(">>"));
	else if (t == AND)
		return (ft_strdup("&&"));
	else if (t == OR)
		return (ft_strdup("||"));
	else if (t == LITERAL)
		return (ft_strdup("lit"));
	return (ft_strdup("interal error"));
}

static void	print_argv(char **argv)
{
	int	arg_i;

	arg_i = 0;
	printf("[%s", RED);
	while (argv[arg_i] != NULL)
		printf("%s, ", argv[arg_i++]);
	printf("\b\b%s]\n", RESET);
}

static void	print_redirs(t_list *redirs)
{
	t_redir	*r;
	int		redir_i;

	redir_i = 0;
	r = get_redir(redirs, redir_i++);
	if (r)
		printf("[");
	else
		printf("[  ");
	while (r != NULL)
	{
		printf("%s%s", BPURPLE, _type_2_str(r->type));
		printf("%s%s%s%s, ", RESET, CYAN, r->val, RESET);
		r = get_redir(redirs, redir_i++);
	}
	printf("\b\b%s]\n", RESET);
}

void	debug_prints_execute_command(char **argv, t_list *l_r, pid_t p_pid)
{
	if (DEBUG_INIT)
	{
		printf("(%s) [%s%d%s] -- spawned from %s%d%s\n",
			argv[0], BLUE, getpid(), RESET, GREEN, p_pid, RESET);
	}
	if (DEBUG_ARGV)
	{
		printf("(%s) [%s%d%s] -- args ", argv[0], BLUE, getpid(), RESET);
		print_argv(argv);
	}
	if (DEBUG_REDIR)
	{
		printf("(%s) [%s%d%s] -- redir ", argv[0], BLUE, getpid(), RESET);
		print_redirs(l_r);
	}
}
