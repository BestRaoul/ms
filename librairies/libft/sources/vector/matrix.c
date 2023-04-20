/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix3d	*new_matrix(t_vec3d *v1, t_vec3d *v2, t_vec3d *v3)
{
	t_matrix3d	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->v1 = v1;
	res->v2 = v2;
	res->v3 = v3;
	return (res);
}

int	valid_matrix(t_matrix3d *m)
{
	return (m && m->v1 && m->v2 && m->v3);
}

void	*free_vectors(t_vec3d *v1, t_vec3d *v2, t_vec3d *v3, t_vec3d *v4)
{
	if (v1)
		free(v1);
	if (v2)
		free(v2);
	if (v3)
		free(v3);
	if (v4)
		free(v4);
	return (NULL);
}

/* Multiplying a 3D matrix with a 3D vector */
t_vec3d	*matrix_mult_vec(t_matrix3d *matrix, t_vec3d *vec)
{
	t_vec3d	*res;
	t_vec3d	*v1;
	t_vec3d	*v2;
	t_vec3d	*v3;

	if (!valid_matrix(matrix) || !vec)
		return (NULL);
	v1 = vec_scale(matrix->v1, vec->x);
	if (!v1)
		return (NULL);
	v2 = vec_scale(matrix->v2, vec->y);
	if (!v2)
		return (free_vectors(v1, 0, 0, 0));
	v3 = vec_scale(matrix->v3, vec->z);
	if (!v3)
		return (free_vectors(v1, v2, 0, 0));
	add_vec_inplace(v2, v3);
	res = vec_add(v2, v1);
	free_vectors(v1, v2, v3, 0);
	return (res);
}

/* Multiplying two 3D matrices */
t_matrix3d	*matrix_mult(t_matrix3d *m1, t_matrix3d *m2)
{
	t_matrix3d	*res;
	t_vec3d		*v1;
	t_vec3d		*v2;
	t_vec3d		*v3;

	v1 = new_vect3d(m1->v1->x * m2->v1->x + m1->v2->x * m2->v1->y + m1->v3->x
			* m2->v1->z, m1->v1->y * m2->v1->x + m1->v2->y * m2->v1->y
			+ m1->v3->y * m2->v1->z, m1->v1->z * m2->v1->x + m1->v2->z
			* m2->v1->y + m1->v3->z * m2->v1->z);
	v2 = new_vect3d(m1->v1->x * m2->v2->x + m1->v2->x * m2->v2->y + m1->v3->x
			* m2->v2->z, m1->v1->y * m2->v2->x + m1->v2->y * m2->v2->y
			+ m1->v3->y * m2->v2->z, m1->v1->z * m2->v2->x + m1->v2->z
			* m2->v2->y + m1->v3->z * m2->v2->z);
	v3 = new_vect3d(m1->v1->x * m2->v3->x + m1->v2->x * m2->v3->y + m1->v3->x
			* m2->v3->z, m1->v1->y * m2->v3->x + m1->v2->y * m2->v3->y
			+ m1->v3->y * m2->v3->z, m1->v1->z * m2->v3->x + m1->v2->z
			* m2->v3->y + m1->v3->z * m2->v3->z);
	res = new_matrix(v1, v2, v3);
	if (!res)
		return (free_vectors(v1, v2, v3, 0));
	if (!valid_matrix(res))
		return (free_matrix3d(res));
	return (res);
}
