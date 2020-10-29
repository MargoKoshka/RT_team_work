#include "rtv1.h"

t_vector	ft_refraction_ray(t_vector *dir, t_vector *norm, float n2)
{
	double		k_refraction;
	double		const_1;
	double		const_2;
	t_vector	refraction_ray;
	t_vector	tmp;

	k_refraction = N_1 / n2;
	refraction_ray = *dir;
	ft_unit_vector(&refraction_ray);
	const_1 = ft_vector_scalar(dir, norm);
	const_2 = sqrt(1 - (k_refraction * k_refraction) * (1 - const_1 * const_1));
	refraction_ray = ft_multiply_vector_num(&refraction_ray, k_refraction);
	tmp = ft_multiply_vector_num(norm, const_2 + k_refraction * const_1);
	refraction_ray = ft_sub_vectors(&refraction_ray, &tmp);
	return (refraction_ray);
}

t_cross		raytrace_refraction(t_rtv *p, t_start *new, float color[][2])
{
	t_cross		refract;

	new->start = ft_multiply_vector_num(&new->intersect, 1.001);
	refract = ft_intersect_objects(p, &new->ray, &new->start);
	if (refract.id == NO_INTERSECT)
		color[new->depth][0] = COLOR_BG_BL;
		// color[new->depth][0] = NO_COLOR;
	else
	{
		refract.vec3 = ft_multiply_vector_num(&new->ray, refract.len);
		new->intersect = ft_add_vectors(&new->intersect, &refract.vec3);
		refract.vec3 = new->intersect;
	}
	return (refract);
}

static void	init_data_refraction(t_start *new, t_start *data)
{
	new->ray = data->ray;
	new->intersect = data->intersect;
	new->depth = 0;
}

static void	calculate_refraction_color(t_rtv *p, t_cross *refract, t_start *new, float color[][2])
{
	new->normal =
	calculate_vector_norm(p->object[refract->id], refract, &new->ray);
	color[new->depth][0] = ft_local_color(p, refract, &new->normal);
	color[new->depth][1] = p->object[refract->id]->refraction;
}

int			ft_refraction(t_rtv *p, t_start *data, double *min_refract)
{
	t_cross		refract;
	t_start		new;
	float		color[p->depth_refract][2];

	init_data_refraction(&new, data);
	while (new.depth < p->depth_refract && *min_refract > MIN_REFRACT)
	{
		refract = raytrace_refraction(p, &new, color);
		if (refract.id == NO_INTERSECT)
			break ;
		calculate_refraction_color(p, &refract, &new, color);
		if (p->object[refract.id]->reflection > 0)
		{
			new.color = ft_reflection(p, &new, min_refract);
			color[new.depth][0] = result_color(color[new.depth][0],
		new.color, p->object[refract.id]->reflection);
		}
		if (p->object[refract.id]->refraction <= 0)
			break ;
		*min_refract *= p->object[refract.id]->refraction;
		new.depth += 1;
	}
	return (calculate_result_color(color, new.depth, p->depth_refract));
}

// new.normal =
// calculate_vector_norm(p->object[refract.id], &refract, &new.ray);
// color[new.depth][0] = ft_local_color(p, &refract, &new.normal);
// color[new.depth][1] = p->object[refract.id]->refraction;
