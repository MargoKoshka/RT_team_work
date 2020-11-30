/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:32:06 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:32:07 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cross		ft_intersect_objects(t_rtv *p, t_vector *ray, t_vector *start)
{
	t_object	tmp_object;
	t_cross		result;
	t_cross		intersect;
	int			n;

	intersect.id = NO_INTERSECT;
	intersect.len = INT_MAX;
	n = 0;
	while (n < p->n_objects)
	{
		tmp_object = *p->object[n];
		if (start != NULL)
			object_data(&tmp_object, start);
		result = ft_raytrace_objects(&tmp_object, ray);
		if (result.id == INTERSECT &&
			result.len > 0.001 && result.len < intersect.len)
		{
			intersect.len = result.len;
			intersect.id = n;
			intersect.check = result.check;
		}
		n += 1;
	}
	return (intersect);
}

int			ft_calculate_color(t_rtv *p, t_vector *ray, t_cross *i)
{
	t_array		color;
	t_start		new;
	double		min_refract;

	color = (t_array){.local = NO_COLOR, \
	.reflect = NO_COLOR, .refract = NO_COLOR};
	new.normal = calculate_vector_norm(p->object[i->id], i, ray);
	new.ray = (t_vector){.x = ray->x, .y = ray->y, .z = ray->z};
	new.intersect = i->vec3;
	color.local = ft_local_color(p, i, &new.normal);
	if (p->object[i->id]->refraction > 0)
	{
		min_refract = p->object[i->id]->refraction;
		color.refract = ft_refraction(p, &new, &min_refract);
	}
	if (p->object[i->id]->reflection > 0)
	{
		min_refract = 1.0;
		color.reflect = ft_reflection(p, &new, &min_refract);
	}
	color.local = result_color(color.local,\
	color.reflect, p->object[i->id]->reflection);
	color.local = result_color(color.local,\
	color.refract, p->object[i->id]->refraction);
	return (color.local);
}

int			ft_color_object(t_rtv *paint, t_vector *ray)
{
	int		color;
	t_cross	intersect;

	intersect = ft_intersect_objects(paint, ray, NULL);
	if (intersect.id == NO_INTERSECT)
		return (COLOR_BG_BL);
	else
	{
		intersect.vec3 = ft_multiply_vector_num(ray, intersect.len);
		color = ft_calculate_color(paint, ray, &intersect);
	}
	return (color);
}

void		*thread_paint_object(void *param)
{
	t_data		*data;
	int			color;

	data = (t_data *)param;
	while (data->y_start < data->y_end)
	{
		data->x = 0;
		while (data->x < data->width)
		{
			color = ft_chose_sampling(data->all, data->x, data->y_start);
			data->all->draw[data->x + data->y_start * data->width] = color;
			data->x += 1;
		}
		data->y_start += 1;
	}
	return (NULL);
}

void		ft_multi_thread_paint(t_rtv *paint)
{
	pthread_t	id[NUM_THREAD];
	t_data		data[NUM_THREAD];
	size_t		n;

	n = 0;
	while (n < NUM_THREAD)
	{
		data[n].all = paint;
		data[n].y_start = n * paint->height / NUM_THREAD;
		data[n].y_end = (n + 1) * paint->height / NUM_THREAD;
		data[n].width = paint->width;
		pthread_create(&id[n], NULL, thread_paint_object, &data[n]);
		n += 1;
	}
	n = 0;
	while (n < NUM_THREAD)
	{
		pthread_join(id[n], NULL);
		n += 1;
	}
}
