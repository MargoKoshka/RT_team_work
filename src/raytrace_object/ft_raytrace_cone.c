/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytrace_cone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:29:46 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:29:47 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	calculate_a_b_c_discr_cone(t_vector *ray, t_object *cone)
{
	double	ray_ray;
	double	ray_norm;
	double	ray_pos;

	ray_ray = ft_vector_scalar(ray, ray);
	ray_norm = ft_vector_scalar(ray, &cone->axis);
	ray_pos = ft_vector_scalar(ray, &cone->pos);
	cone->discr.a = ray_ray - cone->discr.k_tan * (ray_norm * ray_norm);
	cone->discr.b = 2 * (cone->discr.k_tan * ray_norm *\
	cone->discr.pos_n_p - ray_pos);
	cone->discr.c = cone->discr.c;
}

double		ft_intersect_ray_empty_cone(t_vector *ray, t_object *cone)
{
	double	check;

	calculate_a_b_c_discr_cone(ray, cone);
	ft_solve_quadratic_equation(&cone->discr);
	if (cone->discr.discr < 0)
		return (NO_INTERSECT);
	check = check_intersect(ray, &cone->pos, &cone->axis, cone->discr.d_1);
	if (cone->min <= check && check <= cone->max)
		return (cone->discr.d_1);
	check = check_intersect(ray, &cone->pos, &cone->axis, cone->discr.d_2);
	if (cone->min <= check && check <= cone->max)
		return (cone->discr.d_2);
	return (NO_INTERSECT);
}

t_cross		result_data_input(double distance, int check)
{
	t_cross	result;

	result.id = INTERSECT;
	result.len = distance;
	result.check = check;
	return (result);
}

t_cross		calculate_distance_to_cone_caps(t_object *object, t_vector *ray)
{
	t_cross		result;
	t_vector	position;
	t_vector	delta;
	double		angle;
	double		distance;

	angle = ft_vector_scalar(ray, &object->axis);
	if (angle > 0)
		position = ft_multiply_vector_num(&object->axis, object->min);
	else if (angle < 0)
		position = ft_multiply_vector_num(&object->axis, object->max);
	position = ft_add_vectors(&object->pos, &position);
	distance = ft_vector_scalar(&position, &object->axis) / angle;
	delta = ft_multiply_vector_num(ray, distance);
	delta = ft_sub_vectors(&delta, &position);
	result.id = NO_INTERSECT;
	if (angle > 0 && object->r_min *\
	object->r_min - ft_vector_scalar(&delta, &delta) > 0.001)
		return (result_data_input(distance, e_caps));
	if (angle < 0 && object->r_max * object->r_max\
	- ft_vector_scalar(&delta, &delta) > 0.001)
		return (result_data_input(distance, e_caps));
	return (result);
}

t_cross		ft_intersect_ray_cone(t_object *cone, t_vector *ray)
{
	t_cross	result;
	double	check;

	result.id = NO_INTERSECT;
	calculate_a_b_c_discr_cone(ray, cone);
	ft_solve_quadratic_equation(&cone->discr);
	if (cone->discr.discr < 0)
		return (result);
	result = calculate_distance_to_cone_caps(cone, ray);
	check = check_intersect(ray, &cone->pos, &cone->axis, cone->discr.d_1);
	if (cone->min <= check && check <= cone->max)
	{
		if (result.id == INTERSECT && result.len <= cone->discr.d_1)
			return (result);
		return (result_data_input(cone->discr.d_1, e_body));
	}
	check = check_intersect(ray, &cone->pos, &cone->axis, cone->discr.d_2);
	if (cone->min <= check && check <= cone->max)
	{
		if (result.id == INTERSECT && result.len <= cone->discr.d_2)
			return (result);
		return (result_data_input(cone->discr.d_2, e_body));
	}
	return (result);
}
