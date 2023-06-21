/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_min_int(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_abs_int(int a)
{
	if (a < 0)
	{
		if (a == INT_MIN)
			return (INT_MAX);
		else
			return (a * -1);
	}
	return (a);
}
