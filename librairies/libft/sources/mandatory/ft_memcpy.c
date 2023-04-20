/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:49:26 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/13 16:49:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*ptr;
	const char		*ptr2;

	if (dest == 0 && src == 0)
	{
		return (dest);
	}
	i = 0;
	ptr = dest;
	ptr2 = src;
	while (i < n)
	{
		*(ptr + i) = *(ptr2 + i);
		i ++;
	}
	return (dest);
}
