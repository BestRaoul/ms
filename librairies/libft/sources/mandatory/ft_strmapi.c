/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:35:47 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/27 15:35:48 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	index;
	char	*res;

	index = 0;
	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (0);
	while (index < ft_strlen(s))
	{
		res[index] = f(index, s[index]);
		index ++;
	}
	res[index] = 0;
	return (res);
}
