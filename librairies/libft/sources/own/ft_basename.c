/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Gets base name from a path. Ex: /home/user/test -> test */
char	*ft_basename(const char *path)
{
	char	**split_res;
	char	*res;

	split_res = ft_split(path, ft_getsep());
	if (!split_res)
		return (NULL);
	if (ft_strarrlen(split_res) < 1)
		return (NULL);
	res = ft_strdup(split_res[ft_strarrlen(split_res) - 1]);
	ft_free_split(split_res, ft_strarrlen(split_res));
	return (res);
}
