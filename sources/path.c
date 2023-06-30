/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2023/06/29 15:38:52 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

static int	is_bin_in_dir(char *dirname, char *binname)
{
	struct dirent	*dir;
	DIR				*d;

	if (access(dirname, R_OK))
		return (0);
	d = opendir(dirname);
	if (d == NULL)
		crash();
	dir = readdir(d);
	while (dir != NULL)
	{
		if (ft_strequal(dir->d_name, binname))
			return (1);
		dir = readdir(d);
	}
	closedir(d);
	return (0);
}

/*static char	*strarrlast(char **strarr)
{
	if (strarr == NULL || ft_strarrlen(strarr) == 0)
		return (NULL);
	return (strarr[ft_strarrlen(strarr) - 1]);
}*/

char	*where_bin(char *binname)
{
	char	**strarr;

	strarr = ft_environ_to_path_strarr(g_.env);
	while (strarr && *strarr)
	{
		if (is_bin_in_dir(*strarr, binname))
			return (ft_joinpaths(*strarr, binname, NULL));
		strarr++;
	}
	if (access(binname, X_OK))
		return (NULL);
	return (ft_strdup(binname));
}

/*
 * char	**spltres;
	char	*_b;
	char	*_p;
	spltres = ft_split(binname, '/');
	if (strarrlast(spltres) == NULL)
		return (NULL);
	_b = strarrlast(spltres);
	spltres[ft_strarrlen(spltres) - 1] = NULL;
	_p = ft_strarr_to_str(spltres, '/');
	if (ft_str_startswith(binname, "/"))
		_p = ft_strjoin("/", _p);
	dprintf(2, ".p .b, .%s. .%s.\n", _p, _b);
	if (is_bin_in_dir(_p, _b))
		return (ft_joinpaths(_p, _b, NULL));
 */
