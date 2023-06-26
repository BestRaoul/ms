/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:14:39 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:40 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	key_match(char *key, char *entry)
{
	int		eq_i;

	eq_i = ft_find('=', entry);
	if (eq_i == -1)
		return (-1);
	return (ft_strncmp(key, entry, len(key)) == 0
		&& ft_strncmp(key, entry, eq_i) == 0);
}

//-1 if not found
int	find_in_env(char *key)
{
	int	i;

	i = 0;
	while (g_.env[i])
	{
		if (key_match(key, g_.env[i]))
			return (i);
		i++;
	}
	return (-1);
}

/* only reallocates the env PTR
the others are just ported over*/
int	add_var_to_env(char *key, char *value)
{
	char	**old;
	int		i;

	if (find_in_env(key) != -1)
		remove_var_from_env(key);
	old = g_.env;
	g_.env = ft_calloc(strarr_count(old) + 1 + 1, sizeof(char *));
	garbage_collector(REMOVE, g_.env);
	garbage_collector(ADD, old);
	i = 0;
	while (old[i])
	{
		g_.env[i] = old[i];
		i++;
	}
	g_.env[i] = ft_strjoin2(key, "=", value, NULL);
	garbage_collector(REMOVE, g_.env[i]);
	g_.env[++i] = NULL;
	return (0);
}

/* if does not find KEY return 0
else removes it and return 1*/
int	remove_var_from_env(char *key)
{
	char	**old;
	int		i;
	int		j;

	if (find_in_env(key) == -1)
		return (0);
	old = g_.env;
	g_.env = ft_calloc(strarr_count(old), sizeof(char *));
	garbage_collector(REMOVE, g_.env);
	garbage_collector(ADD, old);
	i = 0;
	j = 0;
	while (old[i])
	{
		if (key_match(key, old[i]))
			garbage_collector(ADD, old[i]);
		else
			g_.env[j++] = old[i];
		i++;
	}
	g_.env[j] = NULL;
	return (1);
}

void	print_env(void)
{
	char	**envv;

	envv = g_.env;
	while (*envv)
	{
		ft_printf("%s\n", *envv);
		envv++;
	}
}
