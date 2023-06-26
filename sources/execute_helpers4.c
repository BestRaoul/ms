/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkondrac <pkondrac@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by pkondrac          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by pkondrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define ERROR_MSG "ms: "

static void	elegant_error_consumption(char *s)
{
	int	err;

	err = errno;
	ft_dprintf(2, ERROR_MSG"%s: %s\n", s, strerror(err));
	errno = err;
}

static void	consume_redirs_firstpass(t_list *redirs, int *in_i, int *out_i)
{
	t_redir	*r;
	int		redir_i;

	*in_i = -1;
	*out_i = -1;
	redir_i = 0;
	r = get_redir(redirs, redir_i++);
	while (r != NULL)
	{
		if (r->type == REDIR_L || r->type == HEREDOC || r->type == PIPE_IN)
			*in_i = redir_i;
		else if (r->type == REDIR_R || r->type == APPEND)
			*out_i = redir_i;
		else if (r->type == PIPE_OUT && *out_i == -1)
			*out_i = redir_i;
		r = get_redir(redirs, redir_i++);
	}
	if (DEBUG_REDIR)
	{
		printf("[%d] %d > %d\n", getpid(), *in_i, *out_i);
	}
}

static int	consume_redirs_secondpass(t_list *redirs, int in_i, int out_i)
{
	t_redir	*r;
	int		redir_i;
	int		temp_fd;

	redir_i = 0;
	r = get_redir(redirs, redir_i++);
	while (r != NULL)
	{
		if (redir_i != in_i && redir_i != out_i && r->type != PARENTHESIS)
		{
			if (r->type == REDIR_R || r->type == APPEND)
				temp_fd = open(r->val, O_CREAT | O_WRONLY | O_TRUNC,
						(unsigned int)00664);
			else if (r->type == REDIR_L)
				temp_fd = access(r->val, R_OK);
			else
				temp_fd = ft_atoi(r->val);
			if (r->type == REDIR_L && temp_fd == -1)
				return (elegant_error_consumption(r->val), -1);
			if (temp_fd == -1 || close(temp_fd) == -1)
				crash();
		}
		r = get_redir(redirs, redir_i++);
	}
	return (0);
}

#define RR 0x601
#define AP 0x209

static int	consume_redirs_thirdpass(t_list *redirs, int in_i, int out_i)
{
	t_redir	*r;
	int		redir_i;
	int		to;
	int		from;

	redir_i = 0;
	r = get_redir(redirs, redir_i++);
	while (r != NULL)
	{
		if (redir_i == in_i || redir_i == out_i)
		{
			from = STDIN_FILENO + STDOUT_FILENO * (r->type == REDIR_R
					|| r->type == APPEND || r->type == PIPE_OUT);
			to = ft_atoi(r->val);
			if (r->type == REDIR_L || r->type == REDIR_R || r->type == APPEND)
				to = open(r->val, RR * (r->type == REDIR_R)
						+ AP * (r->type == APPEND), (unsigned int)00664);
			if (to == -1)
				return (elegant_error_consumption(r->val), -1);
			if (dup2(to, from) == -1 || close(to) == -1)
				crash();
		}
		r = get_redir(redirs, redir_i++);
	}
	return (0);
}

//ENS
//returns -1 if failed to consume access redir
int	consume_redirs(t_list *redirs)
{
	int	in_i;
	int	out_i;

	consume_redirs_firstpass(redirs, &in_i, &out_i);
	if (consume_redirs_secondpass(redirs, in_i, out_i) == -1)
		return (-1);
	if (consume_redirs_thirdpass(redirs, in_i, out_i) == -1)
		return (-1);
	return (0);
}
