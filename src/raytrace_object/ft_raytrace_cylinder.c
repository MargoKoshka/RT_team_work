#include "rtv1.h"

static void	calculate_a_b_c_discr_cylindr(t_object *cylindr, t_vector *ray)
{
	t_vector	v1;

	v1 = ft_multiply_vector_num(&cylindr->axis,\
								ft_vector_scalar(ray, &cylindr->axis));
	v1 = ft_sub_vectors(ray, &v1);
	cylindr->discr.a = ft_vector_scalar(&v1, &v1);
	cylindr->discr.b = 2 * ft_vector_scalar(&v1, &cylindr->discr.v2);
}

void	calculate_distance_to_caps(t_vector *ray, t_object *object, t_cross *result)
{
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
	if (ft_vector_scalar(&delta, &delta) <= (object->radius * object->radius))
	{
		result->id = INTERSECT;
		result->len = distance;
		result->check = e_caps;
	}
}

t_cross		ft_intersect_ray_cylinder(t_object *cylindr, t_vector *ray)
{
	t_cross		result;
	double		check;

	result.id = NO_INTERSECT;
	calculate_a_b_c_discr_cylindr(cylindr, ray);
	ft_solve_quadratic_equation(&cylindr->discr);
	if (cylindr->discr.discr < 0)
	{
		calculate_distance_to_caps(ray, cylindr, &result);
		return (result);
	}
	if (cylindr->discr.discr >= 0 && cylindr->discr.d_2 > 0.001f)
	{
		check = check_intersect(ray, &cylindr->pos, &cylindr->axis, cylindr->discr.d_1);
		if (cylindr->min <= check && check <= cylindr->max)
		{
			result.id = INTERSECT;
			result.len = cylindr->discr.d_1;
			result.check = e_body;
			return (result);
		}
	}
	calculate_distance_to_caps(ray, cylindr, &result);
	return (result);
}

t_cross		ft_intersect_ray_tube(t_object *tube, t_vector *ray)
{
	t_cross		result;
	double		check;

	result.id = NO_INTERSECT;
	calculate_a_b_c_discr_cylindr(tube, ray);
	ft_solve_quadratic_equation(&tube->discr);
	if (tube->discr.discr < 0.001)
		return (result);
	check = check_intersect(ray, &tube->pos, &tube->axis, tube->discr.d_1);
	if (tube->max >= check && check >= tube->min)
	{
		result.id = INTERSECT;
		result.len = tube->discr.d_1;
		return (result);
	}
	check = check_intersect(ray, &tube->pos, &tube->axis, tube->discr.d_2);
	if (tube->max >= check && check >= tube->min)
	{
		result.id = INTERSECT;
		result.len = tube->discr.d_2;
	}
	return (result);
}

// double		ft_intersect_circle_plane(t_vector *ray, t_object *plane, double r)
// {
// 	double		len_dist;
// 	double		angle;
// 	t_vector	delta;

// 	angle = ft_vector_scalar(&plane->axis, ray);
// 	if (angle >= 0)
// 		return (NO_INTERSECT);
// 	len_dist = ft_vector_scalar(&plane->pos, &plane->axis) / angle;
// 	if (len_dist == NO_INTERSECT)
// 		return (NO_INTERSECT);
// 	delta = ft_multiply_vector_num(ray, len_dist);
// 	delta= ft_sub_vectors(&delta, &plane->pos);
// 	if (ft_vector_scalar(&delta, &delta) > (r * r))
// 		return (NO_INTERSECT);
// 	return (len_dist);
// }
