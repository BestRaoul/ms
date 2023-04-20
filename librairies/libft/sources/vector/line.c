/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_line3d(t_line3d *line3d)
{
	free(line3d->p1);
	free(line3d->p2);
	free(line3d->v1);
	free(line3d);
}

t_line3d	*line_from_points(t_vec3d *p1, t_vec3d *p2)
{
	t_line3d	*res;

	if (p1 == NULL || p2 == NULL)
		return (NULL);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->p1 = p1;
	res->p2 = p2;
	res->v1 = vec_sub(p2, p1);
	if (!res->v1)
	{
		free(res->p1);
		free(res->p2);
		return (NULL);
	}
	return (res);
}

t_line3d	*line_from_point_and_vec(t_vec3d *p, t_vec3d *d)
{
	t_line3d	*res;

	if (p == NULL || d == NULL)
		return (NULL);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->p1 = p;
	res->v1 = d;
	res->p2 = vec_add(p, d);
	if (!res->p2)
	{
		free(res->p1);
		free(res->v1);
		return (NULL);
	}
	return (res);
}
