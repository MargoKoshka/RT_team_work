#include "rtv1.h"

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

t_vector	calculate_vector_norm(t_object *object, t_cross *intersect, t_vector *ray)
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
	check_normal(ray, &norm);
	return (norm);
}

// t_vector	ft_calculate_vector_norm(t_object *object, t_vector *intersect)
// {
// 	t_vector	norm;
// 	t_vector	v_norm;
// 	double		len_ray;

// 	if (object->id == 'P')
// 		norm = object->axis;
// 	if (object->id == 'S' || object->id == 'C' || object->id == 'K')
// 	{
// 		norm = ft_sub_vectors(intersect, &object->pos);
// 		if (object->id == 'C' || object->id == 'K')
// 		{
// 			len_ray =
// 			ft_vector_projection_on_ray(&norm, &object->axis);
// 			if (object->id == 'K')
// 				len_ray = len_ray /(cos(0.5 * object->angle) *
// 				cos(0.5 * object->angle));
// 			v_norm = ft_multiply_vector_num(&object->axis, len_ray);
// 			norm = ft_subtraction_vector(&norm, &v_norm);
// 		}
// 		ft_unit_vector(&norm);
// 	}
// 	return (norm);
// }

// t_vector	ft_calculate_vector_norm(t_rtv *p, int id, t_vector *intersect)
// {
// 	t_vector	norm;
// 	t_vector	v_norm;
// 	double		len_ray;

// 	if (p->object[id]->id == 'P')
// 		norm = p->object[id]->axis;
// 	if (p->object[id]->id == 'S' || p->object[id]->id == 'C' ||
// 			p->object[id]->id == 'K')
// 	{
// 		norm = ft_sub_vectors(intersect, &p->object[id]->pos);
// 		if (p->object[id]->id == 'C' || p->object[id]->id == 'K')
// 		{
// 			len_ray =
// 			ft_vector_projection_on_ray(&norm, &p->object[id]->axis);
// 			if (p->object[id]->id == 'K')
// 				len_ray = len_ray /(cos(0.5 * p->object[id]->angle) *
// 				cos(0.5 * p->object[id]->angle));
// 			v_norm = ft_multiply_vector_num(&p->object[id]->axis, len_ray);
// 			norm = ft_sub_vectors(&norm, &v_norm);
// 		}
// 		ft_unit_vector(&norm);
// 	}
// 	return (norm);
// }

// cylindr
// len_norm = ABS(ft_vector_modul(&normal));
// if (object->radius - len_norm > 0.001f)
// 	return (object->axis);
// ft_unit_vector(&normal);

// cone
// t_vector	normal;
// t_vector	v_normal;
// double		len_ray;
// double		half_angle;
// double		len_cups;

// half_angle = cos(0.5 * object->angle);
// normal = ft_sub_vectors(intersect, &object->pos);
// len_cups = ft_vector_projection_on_ray(&normal, &object->axis);
// len_ray = len_cups / (half_angle * half_angle);
// v_normal = ft_multiply_vector_num(&object->axis, len_ray);
// normal = ft_sub_vectors(&normal, &v_normal);
// ft_unit_vector(&normal);
// if (object->min - len_cups < -0.001 && object->max - len_cups > 0.001)
// 	return (normal);

// hemisphere
// t_vector	normal;
// double		len_normal;

// normal = ft_sub_vectors(&intersect->vec3, &object->pos);
// len_normal = ft_vector_modul(&normal);
// if (object->radius - len_normal >= 0.001)
// 	normal = object->axis;

/*
t_vector	vector_norm_cone(t_object *object, t_cross *intersect)
{
	t_vector	normal;
	// t_vector	v_normal;
	// double		len_ray;
	// double		half_angle;
	// double		len_cups;

	// half_angle = cos(0.5 * object->angle);
	// normal = ft_sub_vectors(&intersect->vec3, &object->pos);
	// len_cups = ft_vector_projection_on_ray(&normal, &object->axis);
	// len_ray = len_cups / (half_angle * half_angle);
	// v_normal = ft_multiply_vector_num(&object->axis, len_ray);
	// normal = ft_sub_vectors(&normal, &v_normal);
	// ft_unit_vector(&normal);
	// if (object->min - len_cups < -0.001 && object->max - len_cups > 0.001)
	// 	return (normal);

	if (intersect->check == e_body)
		normal = vector_norm_empty_cone(object, intersect);
	if (intersect->check == e_caps)
		normal = object->axis;
	return (normal);
}
*/
