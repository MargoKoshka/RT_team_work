/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:31:25 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:31:26 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		illumination(int specular,
					t_vector *ray, t_vector *reflect, t_vector *norm)
{
	double	shade;
	double	shine;

	shine = 0.0;
	shade = ft_vector_scalar(norm, ray);
	if (shade < 0)
		shade = 0;
	if (shade >= 0 && specular != 0)
		shine = ft_vector_scalar(ray, reflect);
	if (shine > 0)
		shade = shade + powf(shine, specular);
	return (shade);
}

double		is_point_shadow(t_object **object, t_vector *intersect, \
t_vector *ray, double *k_light)
{
	t_object	tmp_object;
	t_vector	new_start;
	double		len_light;
	t_cross		obj;
	int			n;

	len_light = ft_vector_modul(ray);
	ft_unit_vector(ray);
	new_start = ft_multiply_vector_num(intersect, 0.99);
	*k_light = 1.0;
	n = 0;
	while (NULL != object[n])
	{
		tmp_object = *object[n];
		object_data(&tmp_object, &new_start);
		obj = ft_raytrace_objects(&tmp_object, ray);
		if ((0.001 < obj.len && obj.len < len_light) && obj.id == INTERSECT)
		{
			*k_light *= tmp_object.refraction;
			if (tmp_object.refraction == 0)
				return (*k_light);
		}
		n += 1;
	}
	return (*k_light);
}

t_vector	ft_vector_light_cross(t_light *source, t_vector *intersect)
{
	t_vector light_cross;

	if (source->type == e_point)
		light_cross = ft_sub_vectors(&source->pos, intersect);
	if (source->type == e_direct)
		light_cross = source->direction;
	return (light_cross);
}

double		ft_calculate_lighting(t_rtv *p, t_cross *cross, t_vector *norm)
{
	t_vector	light_cross;
	t_vector	reflect;
	int			num;
	double		k_light;
	double		shade;

	shade = 0.0;
	num = 0;
	while (num < p->n_lights)
	{
		if (p->lights[num]->type == e_ambient)
			shade += p->lights[num]->intensity;
		if (p->lights[num]->type == e_point || p->lights[num]->type == e_direct)
		{
			light_cross = ft_vector_light_cross(p->lights[num], &cross->vec3);
			reflect = ft_reflection_ray(&cross->vec3, norm);
			k_light = is_point_shadow(p->object, &cross->vec3, \
			&light_cross, &k_light);
			shade += p->lights[num]->intensity * k_light *
	illumination(p->object[cross->id]->specular, &light_cross, &reflect, norm);
		}
		num++;
	}
	return (shade);
}
