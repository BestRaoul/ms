/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:36:52 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/18 14:36:54 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strnstr_clamp(int val, int min, int max)
{
	if (val > max)
		return (max);
	if (val < min)
		return (min);
	return (val);
}

static int	charseq(unsigned char a, unsigned char b)
{
	a = ft_tolower(a);
	b = ft_tolower(b);
	return (a == b);
}

int	ft_istrncmp(const char *s1, const char *s2, size_t n)
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
		if (!charseq(us1[i], us2[i]))
			return (strnstr_clamp(us1[i] - us2[i], -1, 1));
		if (i + 1 == n)
			return (strnstr_clamp(us1[i] - us2[i], -1, 1));
		i ++;
	}
	return (strnstr_clamp(us1[i] - us2[i], -1, 1));
}
