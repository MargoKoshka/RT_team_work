/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_vector_normal.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:31:53 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:31:54 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		check_normal(t_vector *dir, t_vector *normal)
{
	if (ft_vector_scalar(dir, normal) > 0)
		*normal = ft_multiply_vector_num(normal, -1);
}

t_vector	vector_norm_sphere(t_object *object, t_cross *intersect)
{
	t_vector	normal;

	normal = ft_sub_vectors(&intersect->vec3, &object->pos);
	ft_unit_vector(&normal);
	return (normal);
}

t_vector	vector_norm_hemisphere(t_object *object, t_cross *intersect)
{
	t_vector	normal;

	if (intersect->check == e_body)
		normal = ft_sub_vectors(&intersect->vec3, &object->pos);
	else
		normal = object->axis;
	ft_unit_vector(&normal);
	return (normal);
}

t_vector	calculate_vector_norm(t_object *object,\
t_cross *intersect, t_vector *ray)
{
	t_vector	norm;

	if (object->type == e_plane)
		norm = object->axis;
	if (object->type == e_sphere)
		norm = vector_norm_sphere(object, intersect);
	if (object->type == e_tube)
		norm = vector_norm_tube(object, intersect);
	if (object->type == e_cone)
		norm = vector_norm_cone(object, intersect);
	if (object->type == e_hemisphere)
		norm = vector_norm_hemisphere(object, intersect);
	if (object->type == e_ring)
		norm = vector_norm_sphere(object, intersect);
	if (object->type == e_cylindr)
		norm = vector_norm_cylindr(object, intersect);
	if (object->type == e_paraboloid)
		norm = vector_norm_paraboloid(object, intersect);
	check_normal(ray, &norm);
	return (norm);
}
