/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_envvar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:32 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 12:42:36 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

#define DEBUG_ENV 0

static void	handle_handle_dd(char ***out, char **literal, int *j)
{
	(*out)[*j] = handle_dd();
	(*literal) += 2;
	(*j)++;
}

static void	handle_handle_status(char ***out, char **literal, int *j)
{
	(*out)[*j] = handle_status();
	(*literal) += 2;
	(*j)++;
}

static char	*ret(char **out, int j)
{
	char	*result;

	out[j] = NULL;
	result = join(out, "");
	frees2(1, 1, out, 0);
	return (result);
}

int	cond(char ***out, char **literal, int *j)
{
	if ((*literal)[0] == 0)
		return (1);
	if ((*literal)[1] && (*literal)[1] == '$')
	{
		handle_handle_dd(out, literal, j);
		return (2);
	}
	if ((*literal)[1] && (*literal)[1] == '?')
	{
		handle_handle_status(out, literal, j);
		return (2);
	}
	return (0);
}

char	*handle_env(char *literal)
{
	char	**out;
	int		j;
	int		x;
	int		cond_res;

	out = ft_calloc((2 + 2 * count('$', literal)), sizeof(char *));
	j = 0;
	while (*literal)
	{
		x = find_ne_nqs('$', literal, "\'");
		out[j] = chop(literal, x - 1);
		literal += ft_strlen_int(out[j]);
		j++;
		cond_res = cond(&out, &literal, &j);
		if (cond_res == 1)
			break ;
		if (cond_res == 2)
			continue ;
		literal++;
		out[j] = handle_var(_scan2(&(literal), is_aznum));
		j++;
	}
	return (ret(out, j));
}
