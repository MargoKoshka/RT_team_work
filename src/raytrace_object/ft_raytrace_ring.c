#include "rtv1.h"

double	calc_angle(t_vector *pos, t_vector *axis, t_vector *intersect,
					double min)
{
	t_vector	check;
	double		angle;

	if (min == 0.0)
		check = ft_sub_vectors(intersect, pos);
	else
	{
		check = ft_multiply_vector_num(axis, min);
		check = ft_add_vectors(pos, &check);
		check = ft_sub_vectors(intersect, &check);
	}
	ft_unit_vector(&check);
	angle = ft_vector_scalar(&check, axis);
	return (angle);
}

void	init_axis(t_object *ring, t_vector *axis)
{
	axis[0] = (t_vector){1, 0, 0};
	ft_rotate_vector(&ring->angle_n, &axis[0]);
	axis[1] = (t_vector){0, 1, 0};
	ft_rotate_vector(&ring->angle_n, &axis[1]);
	axis[2] = (t_vector){0, 0, 1};
	ft_rotate_vector(&ring->angle_n, &axis[2]);
}

int		check_intersect_ring(t_object *ring, t_vector *intersect)
{
	t_vector	axis[3];
	double		angle_1;
	double		angle_2;
	int			n;

	init_axis(ring, axis);
	n = 0;
	while (n < 3)
	{
		angle_1 = calc_angle(&ring->pos, &axis[n], intersect, -ring->min);
		angle_2 = calc_angle(&ring->pos, &axis[n], intersect, ring->min);
		if (angle_1 >= 0.001f && angle_2 <= 0.001f)
			n += 1;
		else
			break ;
	}
	if (n != 3)
		return (NO_INTERSECT);
	return (INTERSECT);
}

t_cross	ft_intersect_ray_ring(t_object *ring, t_vector *ray)
{
	t_cross		result;
	t_vector	intersect;
	double		proection_ray;
	double		len;

	result.id = NO_INTERSECT;
	proection_ray = ft_vector_projection_on_ray(&ring->pos, ray);
	len = ring->radius * ring->radius - ring->len_pos * ring->len_pos +
			proection_ray * proection_ray;
	if (len < 0.0)
		return (result);
	result.len = proection_ray - sqrt(len);
	intersect = ft_multiply_vector_num(ray, result.len);
	if (check_intersect_ring(ring, &intersect) == INTERSECT)
	{
		result.id = INTERSECT;
		return (result);
	}
	result.len = proection_ray + sqrt(len);
	intersect = ft_multiply_vector_num(ray, result.len);
	if (check_intersect_ring(ring, &intersect) == INTERSECT)
		result.id = INTERSECT;
	return (result);
}

// double		ft_intersect_ray_hemisphere(t_vector *ray, t_object *sphere)
// {
// 	double		proection_ray;
// 	double		len_dir;
// 	double		len;
// 	double		check;
// 	double		len_plane;

// 	proection_ray = ft_vector_projection_on_ray(&sphere->pos, ray);
// 	len = sphere->radius * sphere->radius - sphere->len_pos * sphere->len_pos +
// 			proection_ray * proection_ray;
// 	if (len < 0)
// 		return (NO_INTERSECT);
// 	len_dir = proection_ray - sqrt(len);
// 	check = check_intersect(ray, &sphere->pos, &sphere->axis, len_dir);
// 	if (check <= sphere->min)
// 		return (len_dir);
// 	len_dir = proection_ray + sqrt(len);
// 	check = check_intersect(ray, &sphere->pos, &sphere->axis, len_dir);
// 	if (check <= sphere->min)
// 	{
// 		len_plane = calculate_len_plane(ray, sphere);
// 		return (len_plane);
// 	}
// 	return (NO_INTERSECT);
// }

/* typedef float float4 __attribute__((ext_vector_type(4)));

float dot(float4 a, float4 b) {
	float4 c = a * 0.5 + b;
	float4 basis[3];
	basis[0].x = 1.f;
	return ((c + a + b).x);
}

float length(float4 v) {
	return (sqrtf(
		v.x * v.x + v.y * v.y + v.z * v.z
	));
}

float4 normalize(float4 v) {
	return (v / length(v));
} */
