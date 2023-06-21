/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "float.h"

double	ft_min_double(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_max_double(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_abs_double(double a)
{
	if (a < 0)
	{
		if (a == DBL_MIN)
			return (DBL_MAX);
		else
			return (a * -1);
	}
	return (a);
}
