/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3d	*new_vect3d(double x, double y, double z)
{
	t_vec3d	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->x = x;
	res->y = y;
	res->z = z;
	return (res);
}

t_vec3d	*vec_add(t_vec3d *v1, t_vec3d *v2)
{
	if (v1 == NULL || v2 == NULL)
		return (NULL);
	return (new_vect3d(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z));
}

t_vec3d	*vec_sub(t_vec3d *v1, t_vec3d *v2)
{
	if (v1 == NULL || v2 == NULL)
		return (NULL);
	return (new_vect3d(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}

t_vec3d	*vec_scale(t_vec3d *v, double scalar)
{
	return (new_vect3d(v->x * scalar, v->y * scalar, v->z * scalar));
}

t_vec3d	*vec_invert(t_vec3d *v)
{
	return (vec_scale(v, -1));
}
