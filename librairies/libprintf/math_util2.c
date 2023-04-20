/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:01:15 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/07 11:01:16 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	my_abs_(int a)
{
	if (a == INT_MIN)
		return (INT_MAX);
	if (a < 0)
		return (a * -1);
	return (a);
}

size_t	size_t_pow(size_t a, size_t b)
{
	size_t	res;
	size_t	i;

	res = 1;
	i = 0;
	while (i < b)
	{
		res *= a;
		i ++;
	}
	return (res);
}
