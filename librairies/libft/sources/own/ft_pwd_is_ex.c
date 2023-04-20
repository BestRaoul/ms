/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_is_ex_and_no_dot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pwd_is_ex(const char *binname, char **envp)
{
	char	*pwd;
	char	*joined;

	pwd = ft_pwd(envp);
	if (!pwd)
		return (0);
	joined = ft_joinpaths(pwd, binname, NULL);
	if (!joined)
	{
		free(pwd);
		return (0);
	}
	if (ft_file_isex(joined))
	{
		free(pwd);
		free(joined);
		return (1);
	}
	free(pwd);
	free(joined);
	return (0);
}
