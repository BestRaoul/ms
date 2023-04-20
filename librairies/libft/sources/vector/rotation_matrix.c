/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix3d	*get_rot_x(double angle)
{
	t_matrix3d	*res;
	t_vec3d		*v1;
	t_vec3d		*v2;
	t_vec3d		*v3;

	v1 = new_vect3d(1, 0, 0);
	v2 = new_vect3d(0, cos_approx(angle), sin_approx(angle));
	v3 = new_vect3d(0, -sin_approx(angle), cos_approx(angle));
	if (!v1 || !v2 || !v3)
		return (free_vectors(v1, v2, v3, 0));
	res = new_matrix(v1, v2, v3);
	if (!res)
		return (free_vectors(v1, v2, v3, 0));
	return (res);
}

t_matrix3d	*get_rot_y(double angle)
{
	t_matrix3d	*res;
	t_vec3d		*v1;
	t_vec3d		*v2;
	t_vec3d		*v3;

	v1 = new_vect3d(cos_approx(angle), 0, -sin_approx(angle));
	v2 = new_vect3d(0, 1, 0);
	v3 = new_vect3d(sin_approx(angle), 0, cos_approx(angle));
	if (!v1 || !v2 || !v3)
		return (free_vectors(v1, v2, v3, 0));
	res = new_matrix(v1, v2, v3);
	if (!res)
		return (free_vectors(v1, v2, v3, 0));
	return (res);
}

t_matrix3d	*get_rot_z(double angle)
{
	t_matrix3d	*res;
	t_vec3d		*v1;
	t_vec3d		*v2;
	t_vec3d		*v3;

	v1 = new_vect3d(cos_approx(angle), sin_approx(angle), 0);
	v2 = new_vect3d(-sin_approx(angle), cos_approx(angle), 0);
	v3 = new_vect3d(0, 0, 1);
	if (!v1 || !v2 || !v3)
		return (free_vectors(v1, v2, v3, 0));
	res = new_matrix(v1, v2, v3);
	if (!res)
		return (free_vectors(v1, v2, v3, 0));
	return (res);
}

/* Return a rotation matrix for a given angle and axis */
t_matrix3d	*get_rotation_matrix(double angle, enum e_rotation axis, int is_rad)
{
	if (!is_rad)
		angle = deg_to_rad(angle);
	if (axis == axis_x)
		return (get_rot_x(angle));
	else if (axis == axis_y)
		return (get_rot_y(angle));
	else
		return (get_rot_z(angle));
}

void	add_angle_to_rotation_matrix(t_matrix3d *rotation_matrix, double angle,
					enum e_rotation axis, int is_rad)
{
	t_matrix3d	*new_matrix;
	t_matrix3d	*rot_mat;

	rot_mat = get_rotation_matrix(angle, axis, is_rad);
	if (!rot_mat)
		return ;
	new_matrix = matrix_mult(rotation_matrix, rot_mat);
	free_matrix3d(rot_mat);
	if (!new_matrix)
		return ;
	free_vectors(rotation_matrix->v1, rotation_matrix->v2,
		rotation_matrix->v3, 0);
	rotation_matrix->v1 = new_matrix->v1;
	rotation_matrix->v2 = new_matrix->v2;
	rotation_matrix->v3 = new_matrix->v3;
	free(new_matrix);
}
