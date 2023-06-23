/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_in_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Checks if a binary is found in a given path.
 * */
int	ft_bin_in_path(const char *binname, const char *path)
{
	char	*full_path;

	full_path = ft_joinpaths(path, binname, NULL);
	if (!full_path)
		return (0);
	if (!ft_file_exists(full_path))
	{
		gc_free(full_path);
		return (0);
	}
	if (!ft_file_isex(full_path))
	{
		gc_free(full_path);
		return (0);
	}
	gc_free(full_path);
	return (1);
}
