/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:31:00 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/17 09:43:01 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  guarantee NUL-termination if there is room */
/* takes in the full dest buffer */
/* !!! room for the terminating NULL must be in the dstsize */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < dstsize - 1 && i < ft_strlen(src))
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}
