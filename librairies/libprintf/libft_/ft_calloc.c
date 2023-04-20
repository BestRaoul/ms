/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:32 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 12:42:36 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_.h"

void	*ft_calloc_(size_t nmemb, size_t size)
{
	void	*res;
	size_t	max_items;
	size_t	hmm;

	if (!size)
	{
		res = malloc(0);
		if (!res)
			return (0);
		return (res);
	}
	hmm = 2147483647;
	max_items = hmm / size;
	if (max_items < nmemb)
		return (0);
	res = malloc(nmemb * size);
	if (!res)
		return (0);
	ft_bzero_(res, nmemb * size);
	return (res);
}
