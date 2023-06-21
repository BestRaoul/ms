/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getpath_ret(char **path_strarr, size_t i, const char *binname)
{
	char	*full_path;

	full_path = ft_joinpaths(path_strarr[i], binname, NULL);
	ft_free_split(path_strarr,
		ft_strarrlen(path_strarr));
	return (full_path);
}

/* checks if a string starts with ./ */
static int	starts_with_cr(const char *str)
{
	if (ft_strlen(str) < 2)
		return (0);
	return (str[0] == '.' && str[1] == ft_getsep());
}

int	ft_getpath_null_check(const char *binname, char **envp)
{
	if (!binname || !envp)
		return (0);
	if (!starts_with_cr(binname) && ft_pwd_is_ex(binname, envp)
		&& ft_chr_in_str(ft_getsep(), binname))
		return (2);
	if (!starts_with_cr(binname) && ft_pwd_is_ex(binname, envp))
		return (0);
	if (ft_str_startswith(binname, "/") && ft_file_isex(binname))
		return (2);
	if (starts_with_cr(binname) && !ft_file_isex(binname))
		return (0);
	return (1);
}
