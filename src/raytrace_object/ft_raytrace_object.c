/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytrace_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:30:02 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:30:03 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_intersect_sphere(t_object *sphere,\
t_vector *ray, t_cross *result)
{
	t_vector	intersect;

	intersect = ft_multiply_vector_num(ray, result->len);
	if (calc_angle(&sphere->pos, &sphere->axis,\
	&intersect, sphere->min) <= 0.001)
	{
		result->id = INTERSECT;
		return (INTERSECT);
	}
	return (NO_INTERSECT);
}

t_cross		ft_intersect_ray_sphere(t_object *sphere, t_vector *ray)
{
	t_cross		result;
	double		proection_ray;
	double		len;

	result.id = NO_INTERSECT;
	proection_ray = ft_vector_projection_on_ray(&sphere->pos, ray);
	len = sphere->radius * sphere->radius - sphere->len_pos * sphere->len_pos +
			proection_ray * proection_ray;
	if (len < 0)
		return (result);
	result.len = proection_ray - sqrt(len);
	if (ft_vector_modul(&sphere->axis) != 0.0)
	{
		if (check_intersect_sphere(sphere, ray, &result) == INTERSECT)
			return (result);
		result.len = proection_ray + sqrt(len);
		if (check_intersect_sphere(sphere, ray, &result) == INTERSECT)
			return (result);
	}
	else
		result.id = INTERSECT;
	return (result);
}

t_cross		ft_intersect_ray_plane(t_object *plane, t_vector *ray)
{
	t_cross		result;
	double		angle;
	t_vector	axis[2];
	t_vector	check;

	result.id = NO_INTERSECT;
	angle = ft_vector_scalar(&plane->axis, ray);
	if (angle >= 0)
		return (result);
	result.len = ft_vector_scalar(&plane->pos, &plane->axis) / angle;
	check = ft_multiply_vector_num(ray, result.len);
	check = ft_sub_vectors(&check, &plane->pos);
	axis[0] = (t_vector){1, 0, 0};
	ft_rotate_vector(&plane->angle_n, &axis[0]);
	axis[1] = (t_vector){0, 0, 1};
	ft_rotate_vector(&plane->angle_n, &axis[1]);
	if (ABS(ft_vector_projection_on_ray(&check, &axis[0])) <= plane->min / 2 &&
		ABS(ft_vector_projection_on_ray(&check, &axis[1])) <= plane->max / 2)
		result.id = INTERSECT;
	return (result);
}

t_cross		ft_raytrace_objects(t_object *object, t_vector *ray)
{
	t_cross		intersect;

	intersect.id = NO_INTERSECT;
	if (object->type == e_sphere)
		intersect = ft_intersect_ray_sphere(object, ray);
	if (object->type == e_plane)
		intersect = ft_intersect_ray_plane(object, ray);
	if (object->type == e_cylindr)
		intersect = ft_intersect_ray_cylinder(object, ray);
	if (object->type == e_tube)
		intersect = ft_intersect_ray_tube(object, ray);
	if (object->type == e_cone)
		intersect = ft_intersect_ray_cone(object, ray);
	if (object->type == e_hemisphere)
		intersect = ft_intersect_ray_hemisphere(object, ray);
	if (object->type == e_ring)
		intersect = ft_intersect_ray_ring(object, ray);
	if (object->type == e_paraboloid)
		intersect = ft_intersect_ray_paraboloid(object, ray);
	return (intersect);
}
