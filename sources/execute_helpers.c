/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <pkondrac@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by pkondrac          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG "TODO: "

void	set_g_status(int err)
{
	if (WIFEXITED(err))
		g_.status = WEXITSTATUS(err);
	else
		g_.status = err;
}

void	reown(char **strr)
{
	int	i;

	i = 0;
	garbage_collector(ADD, strr);
	while (strr[i])
		garbage_collector(ADD, strr[i++]);
}

//IGNORE own pipes as they are closed during consume_redir
void	close_all_pipes(t_list *ignore, int do_crash)
{
	t_redir	*r;
	int		redir_i;
	int		i;

	i = 0;
	while (g_.redirs[i] != NULL)
	{
		if (g_.redirs[i] != ignore)
		{
			redir_i = 0;
			r = get_redir(g_.redirs[i], redir_i++);
			while (r != NULL)
			{
				if (r->type == HEREDOC || r->type == PIPE_IN
					|| r->type == PIPE_OUT)
				{
					if (close(ft_atoi(r->val)) == -1 && do_crash)
						crash();
				}
				r = get_redir(g_.redirs[i], redir_i++);
			}
		}
		i++;
	}
	g_.redirs = NULL;
}

void	close_and_free_all(void)
{
	if (g_.redirs != NULL)
		close_all_pipes(NULL, 0);
	close(g_.dup_stdin);
	close(g_.dup_stdout);
	reown(g_.env);
	garbage_collector(FREE_ALL, 0);
}

void	crash(void)
{
	int	err;

	err = errno;
	close_and_free_all();
	errno = err;
	perror(ERROR_MSG);
	exit(err);
}
