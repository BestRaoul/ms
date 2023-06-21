/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:36:52 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/18 14:36:54 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnstr_clamp(int val, int min, int max)
{
	if (val > max)
		return (max);
	if (val < min)
		return (min);
	return (val);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*us1;
	const unsigned char	*us2;
	size_t				i;

	if (n == 0)
		return (0);
	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	i = 0;
	while (i < n && us1[i] && us2[i])
	{
		if (us1[i] != us2[i])
			return (ft_strnstr_clamp(us1[i] - us2[i], -1, 1));
		if (i + 1 == n)
			return (ft_strnstr_clamp(us1[i] - us2[i], -1, 1));
		i ++;
	}
	return (ft_strnstr_clamp(us1[i] - us2[i], -1, 1));
}
