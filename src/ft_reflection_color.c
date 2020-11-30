/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reflection_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:32:10 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:32:11 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cross		raytrace_reflection(t_rtv *p, t_start *new, float color[][2])
{
	t_cross		reflect;

	new->start = new_start_vector(&new->intersect, &new->ray, 0.001);
	reflect = ft_intersect_objects(p, &new->ray, &new->start);
	reflect.vec3 = ft_multiply_vector_num(&new->ray, reflect.len);
	if (reflect.id == NO_INTERSECT)
		color[new->depth][0] = NO_COLOR;
	else
	{
		reflect.vec3 = ft_multiply_vector_num(&new->ray, reflect.len);
		new->intersect = ft_add_vectors(&new->intersect, &reflect.vec3);
		reflect.vec3 = new->intersect;
	}
	return (reflect);
}

static void	init_data_reflection(t_start *new, t_start *data)
{
	new->ray = ft_reflection_ray(&data->ray, &data->normal);
	new->intersect = data->intersect;
	new->depth = 0;
}

static void	calculate_reflection_color(t_rtv *p,\
t_cross *reflect, t_start *new, float color[][2])
{
	new->normal =
	calculate_vector_norm(p->object[reflect->id], reflect, &new->ray);
	color[new->depth][0] = ft_local_color(p, reflect, &new->normal);
	color[new->depth][1] = p->object[reflect->id]->reflection;
}

int			ft_reflection(t_rtv *p, t_start *data, double *min_refract)
{
	t_cross		reflect;
	t_start		new;
	float		color[p->depth_mirror][2];

	init_data_reflection(&new, data);
	while (new.depth < p->depth_mirror)
	{
		reflect = raytrace_reflection(p, &new, color);
		if (reflect.id == NO_INTERSECT)
			break ;
		calculate_reflection_color(p, &reflect, &new, color);
		if (p->object[reflect.id]->refraction > 0 && *min_refract > MIN_REFRACT)
		{
			*min_refract *= p->object[reflect.id]->refraction;
			new.color = ft_refraction(p, &new, min_refract);
			color[new.depth][0] = result_color(color[new.depth][0], new.color,
			p->object[reflect.id]->refraction);
		}
		if (p->object[reflect.id]->reflection <= 0)
			break ;
		new.depth += 1;
		new.ray = ft_reflection_ray(&new.ray, &new.normal);
	}
	return (calculate_result_color(color, new.depth, p->depth_mirror));
}
