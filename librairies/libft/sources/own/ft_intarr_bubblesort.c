/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intarr_bubblesort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_intarr_bubblesort(const int *arr, size_t len)
{
	int		*res;
	int		swp;
	size_t	i;

	res = gc_malloc(len * sizeof(*res));
	if (!res)
		return (NULL);
	ft_memcpy(res, arr, len * sizeof(*res));
	while (!ft_array_is_sorted(res, len))
	{
		i = 0;
		while (i < len - 1)
		{
			if (res[i] > res[i + 1])
			{
				swp = res[i];
				res[i] = res[i + 1];
				res[i + 1] = swp;
			}
			i ++;
		}
	}
	return (res);
}
