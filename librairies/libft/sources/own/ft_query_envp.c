/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_query_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_query_envp(char *query, char **envp)
{
	size_t	i;
	char	*query_with_equal;
	size_t	len;

	query_with_equal = ft_strjoin_str_chr(query, '=');
	if (!query_with_equal)
		return (NULL);
	len = ft_strlen(query_with_equal);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], query_with_equal, ft_strlen(query_with_equal)))
		{
			FREE(query_with_equal);
			return (ft_strdup(envp[i] + len));
		}
		i ++;
	}
	FREE(query_with_equal);
	return (NULL);
}
