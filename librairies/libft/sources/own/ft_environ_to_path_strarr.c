/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ_to_path_strarr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**final_ret(const char *pth)
{
	if (ft_strlen(pth) < ft_strlen("PATH="))
		return (NULL);
	return (ft_split(pth + ft_strlen("PATH="), ':'));
}

/*
 * Extracts paths from PATH in the environ variable.
 * Returns result in a NULL terminated string array.
 * */
char	**ft_environ_to_path_strarr(char **envp)
{
	char	**res;
	size_t	i;

	res = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (i < ft_strarrlen(envp)
		&& ft_strncmp(envp[i], "PATH", ft_strlen("PATH")))
		i ++;
	if (i == ft_strarrlen(envp))
		return (NULL);
	res = final_ret(envp[i]);
	return (res);
}
