/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:56:12 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/12 15:56:13 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	char			*char_pointer;

	char_pointer = s;
	i = 0;
	while (i < n)
	{
		*(char_pointer + i) = c;
		i ++;
	}
	return (s);
}
