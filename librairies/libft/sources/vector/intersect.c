/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	calc_helper1(t_vec3d **tab, t_line3d *line, t_plane3d *plane)
{
	tab[0] = vec_invert(plane->v1);
	tab[1] = vec_invert(plane->v2);
	tab[2] = vec_sub(plane->p1, line->p1);
}

void	calc_helper2(t_vec3d **tab, t_plane3d *plane, t_vec3d *sol)
{
	tab[0] = vec_scale(plane->v1, sol->y);
	tab[1] = vec_scale(plane->v2, sol->z);
	free(sol);
}

t_vec3d	*line_plane_intersect3d(t_line3d *line, t_plane3d *plane)
{
	t_vec3d	*res;
	t_vec3d	*sol;
	t_vec3d	*calc_vectors[3];

	if (line == NULL || plane == NULL)
		return (NULL);
	calc_helper1(calc_vectors, line, plane);
	if (!calc_vectors[0] || !calc_vectors[1] || !calc_vectors[2])
		return (free_vectors(calc_vectors[0],
				calc_vectors[1], calc_vectors[2], 0));
	sol = solve_general(line->v1, calc_vectors[0],
			calc_vectors[1], calc_vectors[2]);
	free_vectors(calc_vectors[0], calc_vectors[1], calc_vectors[2], 0);
	if (!sol)
		return (free_vectors(sol, 0, 0, 0));
	calc_helper2(calc_vectors, plane, sol);
	if (!calc_vectors[0] || !calc_vectors[1])
		return (free_vectors(calc_vectors[0], calc_vectors[1], 0, 0));
	calc_vectors[2] = vec_add(calc_vectors[0], calc_vectors[1]);
	free_vectors(calc_vectors[0], calc_vectors[1], 0, 0);
	if (!calc_vectors[2])
		free_vectors(calc_vectors[0], calc_vectors[1], calc_vectors[2], 0);
	res = vec_add(plane->p1, calc_vectors[2]);
	free(calc_vectors[2]);
	return (res);
}
