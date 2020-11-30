/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_key_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:26:26 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 14:06:00 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	look(int key, t_rtv *p)
{
	t_vector	start;

	start.x = 0;
	start.y = 0;
	start.z = 0;
	if (key == KEY_S || key == 5)
		start.z -= K_ZOOM;
	else if (key == KEY_W || key == 4)
		start.z += K_ZOOM;
	else if (key == KEY_Q || key == KEY_DOWN)
		start.y -= K_ZOOM;
	else if (key == KEY_E || key == KEY_UP)
		start.y += K_ZOOM;
	else if (key == KEY_A || key == KEY_LEFT)
		start.x -= K_ZOOM;
	else if (key == KEY_D || key == KEY_RIGHT)
		start.x += K_ZOOM;
	ft_rotate_vector(&p->camera->angle, &start);
	p->camera->start.x += start.x;
	p->camera->start.y += start.y;
	p->camera->start.z += start.z;
	calculate_constant(p, &start);
	ft_paint_scene(p);
}

void	rotate_object(int key, t_vector *angle)
{
	if (key == NUM_KEY_6)
		angle->z = K_DIR;
	else if (key == NUM_KEY_4)
		angle->z = -K_DIR;
	else if (key == NUM_KEY_8)
		angle->x = K_DIR;
	else if (key == NUM_KEY_2)
		angle->x = -K_DIR;
	else if (key == NUM_KEY_7)
		angle->y = K_DIR;
	else if (key == NUM_KEY_1)
		angle->y = -K_DIR;
}

void	move_object(int key, t_rtv *p, int num)
{
	if (key == NUM_KEY_8)
		p->object[num]->pos.z += K_MOVE;
	else if (key == NUM_KEY_2)
		p->object[num]->pos.z -= K_MOVE;
	else if (key == NUM_KEY_6)
		p->object[num]->pos.x += K_MOVE;
	else if (key == NUM_KEY_4)
		p->object[num]->pos.x -= K_MOVE;
	else if (key == NUM_KEY_7)
		p->object[num]->pos.y += K_MOVE;
	else if (key == NUM_KEY_1)
		p->object[num]->pos.y -= K_MOVE;
}

void	ft_move_object(int key, t_rtv *p)
{
	int			num;
	t_vector	angle;
	t_vector	move;

	move = (t_vector){0, 0, 0};
	angle = (t_vector){0, 0, 0};
	num = p->selected_obj;
	if (p->visual_effect == e_pull)
	{
		move_object(key, p, num);
	}
	if (p->visual_effect == e_push)
	{
		rotate_object(key, &angle);
		ft_rotate_vector(&angle, &p->object[num]->axis);
	}
	object_data(p->object[num], &move);
	ft_paint_scene(p);
}
