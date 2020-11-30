/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_function_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:30:36 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:30:37 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Multiply Vector x Number(Scalar) and return the resulting Vector;
** result.x = num * vector->x;
** result.y = num * vector->y;
** result.z = num * vector->z;
*/

t_vector	ft_multiply_vector_num(t_vector *vector, double num)
{
	t_vector result;

	result = (t_vector){num * vector->x, num * vector->y, num * vector->z};
	return (result);
}

void		ft_unit_vector(t_vector *vector)
{
	double		modul_v;

	modul_v = ft_vector_modul(vector);
	vector->x /= modul_v;
	vector->y /= modul_v;
	vector->z /= modul_v;
}

t_vector	new_start_vector(t_vector *intersect, t_vector *norm, double delta)
{
	t_vector new_start;

	new_start = ft_multiply_vector_num(norm, delta);
	new_start = ft_add_vectors(intersect, &new_start);
	return (new_start);
}

t_vector	ft_rotation_vector(t_vector *angle, t_vector *ray)
{
	t_vector	dot;
	t_matrix	value;
	double		x;

	value.cos_x = cos(angle->x);
	value.cos_y = cos(angle->y);
	value.cos_z = cos(angle->z);
	value.sin_x = sin(angle->x);
	value.sin_y = sin(angle->y);
	value.sin_z = sin(angle->z);
	dot.y = ray->y * value.cos_x + ray->z * value.sin_x;
	dot.z = -ray->y * value.sin_x + ray->z * value.cos_x;
	dot.x = ray->x * value.cos_y + dot.z * value.sin_y;
	dot.z = -ray->x * value.sin_y + dot.z * value.cos_y;
	x = dot.x;
	dot.x = x * value.cos_z - dot.y * value.sin_z;
	dot.y = x * value.sin_z + dot.y * value.cos_z;
	return (dot);
}

void		ft_rotate_vector(t_vector *angle, t_vector *ray)
{
	t_matrix	value;
	double		y;
	double		x;

	value.cos_x = cos(angle->x);
	value.cos_y = cos(angle->y);
	value.cos_z = cos(angle->z);
	value.sin_x = sin(angle->x);
	value.sin_y = sin(angle->y);
	value.sin_z = sin(angle->z);
	y = ray->y;
	ray->y = y * value.cos_x + ray->z * value.sin_x;
	ray->z = -y * value.sin_x + ray->z * value.cos_x;
	x = ray->x;
	ray->x = x * value.cos_y + ray->z * value.sin_y;
	ray->z = -x * value.sin_y + ray->z * value.cos_y;
	x = ray->x;
	ray->x = x * value.cos_z - ray->y * value.sin_z;
	ray->y = x * value.sin_z + ray->y * value.cos_z;
}
