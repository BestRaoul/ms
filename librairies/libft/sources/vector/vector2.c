/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_vec_inplace(t_vec3d *addee, t_vec3d *added)
{
	addee->x += added->x;
	addee->y += added->y;
	addee->z += added->z;
}

void	sub_vec_inplace(t_vec3d *substractee, t_vec3d *substracted)
{
	substractee->x -= substracted->x;
	substractee->y -= substracted->y;
	substractee->z -= substracted->z;
}

void	scale_vec_inplace(t_vec3d *v, double scalar)
{
	v->x *= scalar;
	v->y *= scalar;
	v->z *= scalar;
}

void	invert_vec_inplace(t_vec3d *v)
{
	scale_vec_inplace(v, -1);
}
