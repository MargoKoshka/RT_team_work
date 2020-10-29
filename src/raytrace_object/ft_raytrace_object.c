#include "rtv1.h"

static int	check_intersect_sphere(t_object *sphere, t_vector *ray, t_cross *result)
{
	t_vector	intersect;
	
	intersect = ft_multiply_vector_num(ray, result->len);
	if (calc_angle(&sphere->pos, &sphere->axis, &intersect, sphere->min) <= 0.001)
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

t_cross	ft_raytrace_objects(t_object *object, t_vector *ray)
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

	return (intersect);
}

double		ft_intersect_ray_cylinder_old(t_vector *ray, t_object *cyl)
{
	t_vector	v1;
	double		check;

	v1 = ft_multiply_vector_num(&cyl->axis,\
								ft_vector_scalar(ray, &cyl->axis));
	v1 = ft_sub_vectors(ray, &v1);
	cyl->discr.a = ft_vector_scalar(&v1, &v1);
	cyl->discr.b = 2 * ft_vector_scalar(&v1, &cyl->discr.v2);
	ft_solve_quadratic_equation(&cyl->discr);
	if (cyl->discr.discr < 0)
		return (NO_INTERSECT);
	check = check_intersect(ray, &cyl->pos, &cyl->axis, cyl->discr.d_1);
	if (cyl->min <= check && check <= cyl->max)
		return (cyl->discr.d_1);
	check = check_intersect(ray, &cyl->pos, &cyl->axis, cyl->discr.d_2);
	if (cyl->min <= check && check <= cyl->max)
		return (cyl->discr.d_2);
	return (NO_INTERSECT);
}

/*
**Check if the ray and cilinder intersect
** FIST
** V_1 = (Ray - ft_vector_scalar(Ray, Nor) * Nor)
** V_1 = ft_multiply_vector_num(Nor, ft_vector_scalar(Ray, Nor))
** V_1 = ft_subtraction_vector(Ray, V_1)
** A = ft_vector_scalar(V_1, V_1)
** V_2 = ft_vector_scalar(Pos, Nor) * Nor) - Pos
** V_2 = ft_multiply_vector_num(Nor, ft_vector_scalar(Pos, Nor))
** V_2 = ft_subtraction_vector(V_2, Pos)
** B = 2 * (Ray - ft_vector_scalar(Ray, Nor) * Nor) * -1 * (Vector_Pos * V_2)
** B = 2 * ft_vector_scalar(V_1, V_2)
** C = ft_vector_scalar(V_2, V_2) - Radius^2
** SECOND
** A = Ray|Ray - (Ray|Nor_p)^2
** B = -2 * (Ray|Pos - (Ray|Nor_p)*(Pos|Nor_p))
** C = Pos|Pos - (Pos|Nor_p)^2 - Radius * Radius
** double discr = B * B - 4 * A * C;
** void		ft_solve_discriminant(t_discr *discr)
** {
** 	discr->discr = discr->b * discr->b - 4 * discr->a * discr->c;
** }
*/

// double		ft_intersect_circle_plane(t_vector *ray, t_object *plane, double r)
// {
// 	double		len_dist;
// 	t_vector	delta;

// 	len_dist = ft_intersect_ray_plane(ray, plane);
// 	if (len_dist == NO_INTERSECT)
// 		return (NO_INTERSECT);
// 	delta = ft_multiply_vector_num(ray, len_dist);
// 	delta= ft_sub_vectors(&delta, &plane->pos);
// 	if (ft_vector_scalar(&delta, &delta) > (r * r))
// 		return (NO_INTERSECT);
// 	return (len_dist);
// }

// double		ft_intersect_ray_cylinder(t_vector *ray, t_object *cil)
// {
// 	t_vector	v1;
// 	t_discr		cilindr;
// 	double		len_dist;

// 	v1 = ft_multiply_vector_num(&cil->axis,\
// 								ft_vector_scalar(ray, &cil->axis));
// 	v1 = ft_sub_vectors(ray, &v1);
// 	cilindr.a = ft_vector_scalar(&v1, &v1);
// 	cilindr.b = 2 * ft_vector_scalar(&v1, &cil->discr.v2);
// 	cilindr.c = cil->discr.c;
// 	len_dist = ft_solve_quadratic_equation(&cilindr);
// 	return (len_dist);
// }

// t_vector	**init_axis(t_object *ring, t_vector **axis)
// {
// 	int n;
// 	axis = (t_vector **)malloc(sizeof(t_vector *) * 4);
// 	if (axis == NULL)
// 		ft_exit(ERR_CREAT_TO_ARR);
// 	n = 0;
// 	while (n < 3)
// 	{
// 		axis[n] = ft_memalloc(sizeof(t_vector));
// 		if (axis[n] == NULL)
// 			ft_exit(ERR_CREAT_TO_ARR);
// 		n += 1;
// 	}
// 	axis[n] =NULL;
// 	*axis[0]= (t_vector){1, 0, 0};
// 	ft_rotate_vector(&ring->angle_n, axis[0]);
// 	*axis[1]= (t_vector){0, 1, 0};
// 	ft_rotate_vector(&ring->angle_n, axis[1]);
// 	*axis[2]= (t_vector){0, 0, 1};
// 	ft_rotate_vector(&ring->angle_n, axis[2]);
// 	// printf("%f %f %f\n", axis[2]->x, axis[2]->y, axis[2]->z);
// 	return (axis);
// }

// double		ft_intersect_ray_cone(t_vector *ray, t_object *cone)
// {
// 	// t_discr	conus;
// 	double	ray_norm;
// 	double	ray_ray;
// 	double	ray_pos;
// 	double	len_dist;

// 	ray_ray = ft_vector_scalar(ray, ray);
// 	ray_norm = ft_vector_scalar(ray, &cone->axis);
// 	ray_pos = ft_vector_scalar(ray, &cone->pos);
// 	// conus.a = ray_ray - cone->discr.k_tan * (ray_norm * ray_norm);
// 	// conus.b = 2 * (cone->discr.k_tan * ray_norm * cone->discr.pos_n_p - ray_pos);
// 	// conus.c = cone->discr.c;
// 	// len_dist = ft_solve_quadratic_equation_2(&conus);
// 	cone->discr.a = ray_ray - cone->discr.k_tan * (ray_norm * ray_norm);
// 	cone->discr.b = 2 * (cone->discr.k_tan * ray_norm * cone->discr.pos_n_p - ray_pos);
// 	cone->discr.c = cone->discr.c;
// 	ft_solve_quadratic_equation(&cone->discr);
// 	if (cone->discr.discr < 0)
// 		return (NO_INTERSECT);
// 	else
// 	{
// 		len_dist = check_intersect_old(ray, cone);
// 		if (len_dist == NO_INTERSECT)
// 			return (NO_INTERSECT);
// 	}
// 	return (len_dist);
// }
