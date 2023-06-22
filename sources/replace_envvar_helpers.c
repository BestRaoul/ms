/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_envvar_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:32 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 12:42:36 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	is_aznum(char c)
{
	return (in(c, "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRST")
		|| in(c, "UVWXYZ0123456789"));
}

char	*handle_dd(void)
{
	char	pid[64];

	pid[0] = 0;
	ft_yoloprintf(pid, "%d", getpid());
	return (ft_strdup(pid));
}

char	*handle_status(void)
{
	char	status[64];

	status[0] = 0;
	ft_yoloprintf(status, "%d", g.status);
	return (ft_strdup(status));
}

char	*handle_var(char *envvar)
{
	int	x;
	int	eq_i;

	if (ft_strlen_int(envvar) == 0)
		return (ft_strdup("$"));
	x = find_in_env(envvar);
	if (x != -1)
	{
		eq_i = ft_find('=', g.env[x]);
		if (eq_i == -1)
		{
			dprintf(2, "env: no `=' in envvar WUT?\n");
			exit(69);
		}
		return (ft_strdup(&(g.env[x][eq_i + 1])));
	}
	return (ft_strdup(""));
}
