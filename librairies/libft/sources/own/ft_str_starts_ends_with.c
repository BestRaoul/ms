/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_starts_ends_with.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:55:21 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/17 17:55:22 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_startswith(const char *str, const char *needle)
{
	if (ft_strlen(str) < ft_strlen(needle))
		return (0);
	if (!ft_strncmp(str, needle, ft_strlen(needle)))
		return (1);
	return (0);
}

int	ft_str_endswith(const char *str, const char *needle)
{
	if (ft_strlen(str) < ft_strlen(needle))
		return (0);
	if (ft_strncmp(str + (ft_strlen(str)
				- ft_strlen(needle)), needle, ft_strlen(needle)))
		return (0);
	return (1);
}
