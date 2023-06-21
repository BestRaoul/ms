/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:12:03 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/19 16:12:04 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	my_clamp2(int val, int min, int max)
{
	if (val > max)
		return (max);
	if (val < min)
		return (min);
	return (val);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_uc;
	const unsigned char	*s2_uc;
	size_t				i;

	if (!n)
		return (0);
	s1_uc = (unsigned char *) s1;
	s2_uc = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (*s1_uc != *s2_uc)
			return (*s1_uc - *s2_uc);
		if (i + 1 == n)
			return (*s1_uc - *s2_uc);
		s1_uc ++;
		s2_uc ++;
		i ++;
	}
	return (0);
}
