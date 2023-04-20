/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:33:36 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/13 17:33:38 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;
	size_t		i;

	if (dest == src)
		return (dest);
	dest_ptr = dest;
	src_ptr = src;
	i = 0;
	while (i < n)
	{
		if (dest > src)
			*(dest_ptr + n - 1 - i) = *(src_ptr + n - 1 - i);
		else
			*(dest_ptr + i) = *(src_ptr + i);
		i ++;
	}
	return (dest);
}
