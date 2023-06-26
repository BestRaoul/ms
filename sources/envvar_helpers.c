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

int	export_valid(char *s)
{
	if (len(s) == 0)
		return (0);
	if (ft_str_startswith(s, "="))
		return (0);
	if (ft_isdigit(*s))
		return (0);
	while (*s)
	{
		if (*s == '=')
			return (1);
		if (!ft_isalnum(*s))
			return (0);
		s++;
	}
	return (1);
}

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
	ft_yoloprintf(status, "%d", g_.status);
	return (ft_strdup(status));
}

char	*handle_var(char *envvar)
{
	int	x;
	int	eq_i;

	if (len(envvar) == 0)
		return (ft_strdup("$"));
	x = find_in_env(envvar);
	if (x != -1)
	{
		eq_i = ft_find('=', g_.env[x]);
		if (eq_i == -1)
		{
			ft_dprintf(2, "env: no `=' in envvar WUT?\n");
			exit(69);
		}
		return (ft_strdup(&(g_.env[x][eq_i + 1])));
	}
	return (ft_strdup(""));
}
