/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:50:27 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 16:19:21 by jwikiera         ###   ########.fr       */
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

static int	find_from_behind(char c, char *s, int start)
{
	while (start >= 0)
	{
		if (s[start] == c)
			return (start);
		start--;
	}
	return (-1);
}

static char	*strarrlast(char **strarr)
{
	if (strarr == NULL || ft_strarrlen(strarr) == 0)
		return (NULL);
	return (strarr[ft_strarrlen(strarr) - 1]);
}

char	*where_bin(char *binname)
{
	char	**strarr;
	char	**spltres;
	char	*_b;
	char	*_p;

	strarr = ft_environ_to_path_strarr(g_.env);
	while (*strarr)
	{
		if (is_bin_in_dir(*strarr, binname))
			return (ft_joinpaths(*strarr, binname, NULL));
		strarr++;
	}
	spltres = ft_split(binname, '/');
	if (!strarrlast(spltres))
		return (NULL);
	_b = strarrlast(spltres);
	spltres[ft_strarrlen(spltres) - 1] = NULL;
	_p = join(spltres, "/");
	if (is_bin_in_dir(_p, _b))
		return (ft_joinpaths(_p, _b));
	return (NULL);
}
