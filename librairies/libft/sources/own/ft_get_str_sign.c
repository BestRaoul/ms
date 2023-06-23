/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_str_sign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_str_sign(const char *str)
{
	char	*trimmed;
	size_t	i;
	int		sign;

	if (!str)
		return (1);
	trimmed = ft_powertrim(str, "");
	if (!trimmed)
		return (1);
	i = 0;
	sign = 1;
	while (trimmed[i] && !ft_isdigit(trimmed[i]))
	{
		if (trimmed[i] == '-')
			sign *= -1;
		i ++;
	}
	gc_free(trimmed);
	return (sign);
}
