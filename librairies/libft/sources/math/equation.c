/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	determinant(t_vec3d *v1, t_vec3d *v2, t_vec3d *v3)
{
	const double	a[] = {v1->x, v1->y, v1->z,
		v2->x, v2->y, v2->z,
		v3->x, v3->y, v3->z};

	return (a[0] * (a[4] * a[8] - a[5] * a[7]) - a[3]
		* (a[1] * a[8] - a[2] * a[7]) + a[6] * (a[1] * a[5] - a[2] * a[4]));
}

t_vec3d	*solve_general(t_vec3d *v1, t_vec3d *v2, t_vec3d *v3, t_vec3d *v_sol)
{
	double			x;
	double			y;
	double			z;
	double			det;
	const double	a[] = {v1->x, v1->y, v1->z,
		v2->x, v2->y, v2->z,
		v3->x, v3->y, v3->z,
		v_sol->x, v_sol->y, v_sol->z};

	det = determinant(v1, v2, v3);
	if (det == 0)
		return (new_vect3d(0, 0, 0));
	x = (a[9] * (a[4] * a[8] - a[5] * a[7]) + a[10]
			* (a[5] * a[6] - a[3] * a[8])
			+ a[11] * (a[3] * a[7] - a[6] * a[4])) / det;
	y = (a[9] * (a[7] * a[2] - a[1] * a[8]) + a[10]
			* (a[0] * a[8] - a[2] * a[6])
			+ a[11] * (a[1] * a[6] - a[7] * a[0])) / det;
	z = (a[9] * (a[1] * a[5] - a[2] * a[4]) + a[10]
			* (a[0] * a[5] - a[2] * a[3])
			+ a[11] * (a[0] * a[4] - a[1] * a[3])) / det;
	return (new_vect3d(x, y, z));
}
