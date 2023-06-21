/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath_current.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fr(char *trimmed, char *sep_prefix)
{
	if (trimmed)
		FREE(trimmed);
	if (sep_prefix)
		FREE(sep_prefix);
	return (NULL);
}

/*
 * If available, returns the path of a given binary, including current dir.
 * */
char	*ft_getpath_current(const char *binname, char **envp)
{
	char	*trimmed;
	char	*sep_prefix;

	trimmed = ft_powertrim(binname, "");
	if (!trimmed)
		return (NULL);
	sep_prefix = MALLOC(sizeof(*sep_prefix) * 3);
	if (!sep_prefix)
		return (fr(trimmed, 0));
	sep_prefix[0] = '.';
	sep_prefix[1] = ft_getsep();
	sep_prefix[2] = '\0';
	if (!ft_strncmp(trimmed, sep_prefix, 2)
		&& ft_bin_in_path(trimmed, "."))
	{
		fr(0, sep_prefix);
		return (trimmed);
	}
	else if (ft_strncmp(trimmed, sep_prefix, 2))
	{
		fr(trimmed, sep_prefix);
		return (ft_getpath(binname, envp));
	}
	return (fr(trimmed, sep_prefix));
}
