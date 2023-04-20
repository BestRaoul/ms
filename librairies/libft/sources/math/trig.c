/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* source: http://www.ganssle.com/item/approximations-for-trig-c-code.htm
 * Cos accuracy: 7.3, tan: 8.2, sin: .
 * Angles are given in radians. */

double	cos_approx(double angle)
{
	const double	c1 = 0.999999953464;
	const double	c2 = -0.4999999053455;
	const double	c3 = 0.0416635846769;
	const double	c4 = -0.0013853704264;
	const double	c5 = 0.000023233;

	return (c1 + angle * angle * (c2 + angle * angle * c3 + angle
			* angle * (c4 + c5 * angle * angle)));
}

double	sin_approx(double angle)
{
	return (cos_approx(HALFPI - angle));
}

double	tan_approx(double angle)
{
	const double	c1 = 211.849369664121;
	const double	c2 = -12.5288887278448;
	const double	c3 = 269.7350131214121;
	const double	c4 = -71.4145309347748;
	double			angle2;

	angle2 = angle * angle;
	return (angle * (c1 + c2 * angle2) / (c3 + angle2 * (c4 + angle2)));
}
