/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  vec2d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec2d	*new_vect2d(double x, double y)
{
	t_vec2d	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->x = x;
	res->y = y;
	return (res);
}
