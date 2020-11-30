/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:29:34 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:29:35 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		check_intersect_old(t_vector *ray, t_object *obj)
{
	t_vector	intersect;
	double		angle_1;
	double		angle_2;

	intersect = ft_multiply_vector_num(ray, obj->discr.d_1);
	angle_1 = calc_angle(&obj->pos, &obj->axis, &intersect, obj->min);
	angle_2 = calc_angle(&obj->pos, &obj->axis, &intersect, obj->max);
	if (angle_1 >= 0.001f && angle_2 <= 0.001f)
		return (obj->discr.d_1);
	intersect = ft_multiply_vector_num(ray, obj->discr.d_2);
	angle_1 = calc_angle(&obj->pos, &obj->axis, &intersect, obj->min);
	angle_2 = calc_angle(&obj->pos, &obj->axis, &intersect, obj->max);
	if (angle_1 >= 0.001f && angle_2 <= 0.001f)
		return (obj->discr.d_2);
	return (NO_INTERSECT);
}

double		check_intersect(t_vector *ray, t_vector *pos,\
t_vector *axis, double len)
{
	t_vector	intersect;
	double		check;

	intersect = ft_multiply_vector_num(ray, len);
	intersect = ft_sub_vectors(&intersect, pos);
	check = ft_vector_projection_on_ray(&intersect, axis);
	return (check);
}
