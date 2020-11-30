/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aliasing_effects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:25:35 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:25:36 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_pixel_color(t_color *color1, int color2)
{
	color1->red += ((color2 >> 16) & 0xFF);
	color1->green += ((color2 >> 8) & 0xFF);
	color1->blue += (color2 & 0xFF);
}

int		avg_pixel_color(t_color *color, int num_samples)
{
	float red;
	float green;
	float blue;

	red = (float)color->red / (float)num_samples;
	green = (float)color->green / (float)num_samples;
	blue = (float)color->blue / (float)num_samples;
	return (((int)red << 16) | ((int)green << 8) | (int)blue);
}

int		ft_chose_sampling(t_rtv *paint, int x, int y)
{
	int			color;
	t_vector	ray;

	color = 0;
	ray.x = (double)x - (double)paint->x0;
	ray.y = (double)paint->y0 - (double)y;
	ray.z = paint->fov;
	if (paint->samples == MIN_SAMPLE)
	{
		ray = ft_rotation_vector(&paint->camera->angle, &ray);
		ft_unit_vector(&ray);
		color = ft_color_object(paint, &ray);
	}
	else
		color = ft_aliasing_effects(paint, &ray);
	return (color);
}

int		ft_aliasing_effects(t_rtv *paint, t_vector *ray)
{
	int			color;
	t_color		pixel_color;
	t_vector	new_ray;
	int			x;
	int			y;

	pixel_color = (t_color){.red = 0, .green = 0, .blue = 0};
	y = 0;
	while (y < paint->samples)
	{
		x = 0;
		while (x < paint->samples)
		{
			new_ray.x = ray->x + ((x + 0.5) / paint->samples);
			new_ray.y = ray->y + ((y + 0.5) / paint->samples);
			new_ray.z = ray->z;
			ft_rotate_vector(&paint->camera->angle, &new_ray);
			ft_unit_vector(&new_ray);
			color = ft_color_object(paint, &new_ray);
			add_pixel_color(&pixel_color, color);
			x += 1;
		}
		y += 1;
	}
	return (avg_pixel_color(&pixel_color, paint->samples * paint->samples));
}
