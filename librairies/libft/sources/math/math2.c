/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "float.h"

float	ft_min_float(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_max_float(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	ft_abs_float(float a)
{
	if (a < 0)
	{
		if (a == FLT_MIN)
			return (FLT_MAX);
		else
			return (a * -1);
	}
	return (a);
}

/* Converting degrees to radians */
double	deg_to_rad(double angle)
{
	return (angle * PI / 180);
}
