/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_ps(t_vec3d *p1, t_vec3d *p2, t_vec3d *p3)
{
	free(p1);
	free(p2);
	free(p3);
}

void	free_plane3d(t_plane3d *plane3d)
{
	free(plane3d->p1);
	free(plane3d->p2);
	free(plane3d->p3);
	free(plane3d->v1);
	free(plane3d->v2);
	free(plane3d);
}

t_plane3d	*plane_from_points(t_vec3d *p1, t_vec3d *p2, t_vec3d *p3)
{
	t_plane3d	*res;

	if (p1 == NULL || p2 == NULL || p3 == NULL)
		return (NULL);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->p1 = p1;
	res->p2 = p2;
	res->p3 = p3;
	res->v1 = vec_sub(p2, p1);
	if (!res->v1)
	{
		free_ps(p1, p2, p3);
		return (NULL);
	}
	res->v2 = vec_sub(p3, p1);
	if (!res->v2)
	{
		free_ps(p1, p2, p3);
		return (NULL);
	}
	return (res);
}

t_plane3d	*plane_from_point_and_vecs(t_vec3d *p, t_vec3d *u, t_vec3d *v)
{
	t_plane3d	*res;

	if (p == NULL || u == NULL || v == NULL)
		return (NULL);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->p1 = p;
	res->v1 = u;
	res->v2 = v;
	res->p2 = vec_add(p, u);
	if (!res->p2)
	{
		free_ps(p, u, v);
		return (NULL);
	}
	res->p3 = vec_add(p, v);
	if (!res->p2)
	{
		free_ps(p, u, v);
		return (NULL);
	}
	return (res);
}
