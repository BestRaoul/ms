/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:33:04 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/19 15:33:05 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s_uc;

	i = 0;
	s_uc = (unsigned char *)s;
	while (i < n)
	{
		if (*s_uc == (unsigned char) c)
			return ((void *) s_uc);
		i ++;
		s_uc ++;
	}
	return (0);
}
