#include "rtv1.h"

/*
** If the camera position is beyond the plane(если камера за плоскостью),
** normal_p = -normal_p.
*/

void		data_plane(t_object *object, t_vector *start)
{
	ft_unit_vector(&object->axis);
	object->pos_cam = ft_vector_scalar(&object->axis, &object->pos) -
		ft_vector_scalar(&object->axis, start);
	if (object->pos_cam > 0.001f)
		object->axis = ft_multiply_vector_num(&object->axis, -1);
}

void		data_cylindr(t_object *object)
{
	ft_unit_vector(&object->axis);
	object->discr.v2 = ft_multiply_vector_num(&object->axis, \
					ft_vector_scalar(&object->pos, &object->axis));
	object->discr.v2 = ft_sub_vectors(&object->discr.v2, &object->pos);
	object->discr.c = ft_vector_scalar(&object->discr.v2, &object->discr.v2) -
						object->radius * object->radius;
}

void		data_cone(t_object *object)
{
	double tangens;
	
	tangens = tan(object->angle / 2);
	ft_unit_vector(&object->axis);
	object->discr.k_tan = 1 + pow(tangens, 2);
	object->discr.pos_n_p = ft_vector_scalar(&object->pos, &object->axis);
	object->discr.c = ft_vector_scalar(&object->pos, &object->pos) -
					object->discr.k_tan * pow(object->discr.pos_n_p, 2);
	object->r_min = ABS(object->min * tangens);
	object->r_max = ABS(object->max * tangens);
}


void		object_data(t_object *object, t_vector *start)
{
	if (object->type == e_plane)
		data_plane(object, start);
	object->pos = ft_sub_vectors(&object->pos, start);
	if (object->type == e_sphere || object->type == e_ring || object->type == e_hemisphere)
		object->len_pos = ft_vector_modul(&object->pos);
		// object->len_pos = object->pos.x * object->pos.x +
		// object->pos.y * object->pos.y + object->pos.z * object->pos.z;
	if (object->type == e_cylindr || object->type == e_tube)
		data_cylindr(object);
	if (object->type == e_cone)
		data_cone(object);
}

void		calculate_constant(t_rtv *p, t_vector *start)
{
	t_light		*tmp;
	int			n;

	tmp = p->light;
	while (tmp != NULL)
	{
		if (tmp->tip == e_point)
			tmp->pos = ft_sub_vectors(&tmp->pos, start);
		tmp = tmp->next;
	}
	n = 0;
	while (NULL != p->object[n])
	{
		object_data(p->object[n], start);
		n += 1;
	}
}

// void		object_data(t_object *object, t_vector *start)
// {
// 	if (object->type == e_plane)
// 		data_plane(object, start);
// 	object->pos = ft_sub_vectors(&object->pos, start);
// 	if (object->type == e_sphere || object->type == e_ring || object->type == e_hemisphere)
// 		object->len_pos = ft_vector_modul(&object->pos);
		// object->len_pos = object->pos.x * object->pos.x +
		// object->pos.y * object->pos.y + object->pos.z * object->pos.z;
	// if (object->type == e_cylindr)
	// {
	// 	ft_unit_vector(&object->axis);
	// 	object->discr.v2 = ft_multiply_vector_num(&object->axis, \
	// 					ft_vector_scalar(&object->pos, &object->axis));
	// 	object->discr.v2 = ft_sub_vectors(&object->discr.v2, &object->pos);
	// 	object->discr.c = ft_vector_scalar(&object->discr.v2, &object->discr.v2)
	// 		- object->radius * object->radius;
	// }
	// if (object->type == e_cone)
	// {
	// 	ft_unit_vector(&object->axis);
	// 	object->discr.k_tan = 1 + pow(tan(object->angle / 2), 2);
	// 	object->discr.pos_n_p = ft_vector_scalar(&object->pos, &object->axis);
	// 	object->discr.c = ft_vector_scalar(&object->pos, &object->pos) -
	// 					object->discr.k_tan * pow(object->discr.pos_n_p, 2);
	// }
// }
