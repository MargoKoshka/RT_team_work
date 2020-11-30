/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_mouse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:26:35 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:26:36 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		mouse_press(int button, int x, int y, t_rtv *p)
{
	if (y >= 0 && y <= (p->height - 1) && x >= 0 && x <= (p->width - 1))
	{
		if (button == MOUSE_LEFT)
		{
			p->mouse_key = e_push;
		}
		if (button == MOUSE_UP || button == MOUSE_DOWN)
			look(button, p);
		if (button == MOUSE_RIGHT)
			selected_object(x, y, p);
	}
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_rtv		*p;

	(void)x;
	(void)y;
	(void)button;
	p = (t_rtv *)param;
	p->mouse_key = e_pull;
	return (0);
}

int		mouse_movement(int x, int y, t_rtv *p)
{
	int			x_start;
	int			y_start;

	x_start = p->mouse_x;
	y_start = p->mouse_y;
	p->mouse_x = x;
	p->mouse_y = y;
	if (y >= 0 && y <= (p->height - 1) && x >= 0 && x <= (p->width - 1))
	{
		if (p->mouse_key == e_push)
		{
			p->camera->angle.y -=\
			asin((double)(x - x_start) / (double)p->width);
			p->camera->angle.x -=\
			asin((double)(y_start - y) / (double)p->width);
			ft_paint_scene(p);
		}
	}
	return (0);
}

void	selected_object(int x, int y, t_rtv *p)
{
	t_cross		result;
	t_vector	ray;

	ray.x = (double)x - (double)p->x0;
	ray.y = (double)p->y0 - (double)y;
	ray.z = p->fov;
	ray = ft_rotation_vector(&p->camera->angle, &ray);
	ft_unit_vector(&ray);
	result = ft_intersect_objects(p, &ray, NULL);
	p->selected_obj = result.id;
}
