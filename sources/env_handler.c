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
	char	**spltres;
	int		res;

	spltres = ft_split(entry, '=');
	if (!spltres || ft_strarrlen(spltres) < 2)
	{
		free_arr((void **) spltres);
		return (0);
	}
	res = ft_strequal(key, spltres[0]);
	free_arr((void **) spltres);
	return (res);
}

char	**copy_env(char **env, char *excl)
{
	char	**res;
	t_list	*lst;
	char	*tmp;

	lst = NULL;
	while (*env)
	{
		if (excl && key_match(excl, *env))
		{
			env ++;
			continue ;
		}
		tmp = ft_strdup(*env);
		ft_lstadd_str(tmp, &lst);
		env++;
	}
	res = ft_tlst_to_strarr(lst);
	ft_lstclear(&lst, ft_delnode);
	return (res);
}

void	print_env()
{
	char	**envv;

	envv = g.env;
	while (*envv)
	{
		ft_printf("%s\n", *envv);
		envv++;
	}
}

int	add_var_to_env(char *key, char *value)
{
	char	*res;
	int		int_res;

	res = ft_strjoin2(key, "=", value, NULL);
	if (!res)
		return (0);
	int_res = ft_strarr_append_str(&(g.env), res);
	FREE(res);
	return (int_res);
}

int	remove_var_from_env(char *key)
{
	char	**res;

	res = copy_env(g.env, key);
	free_arr((void **) g.env);
	g.env = res;
	return (1);
}
