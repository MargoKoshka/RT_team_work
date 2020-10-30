/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 16:09:11 by wrhett            #+#    #+#             */
/*   Updated: 2020/10/18 16:34:28 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// void	look(int key, t_rtv *p)
// {
// 	if (key == KEY_S)
// 		p->camera->angle.x -= K_DIR;
// 	else if (key == KEY_W)
// 		p->camera->angle.x += K_DIR;
// 	else if (key == KEY_A)
// 		p->camera->angle.y -= K_DIR;
// 	else if (key == KEY_D)
// 		p->camera->angle.y += K_DIR;
// 	else if (key == KEY_Q)
// 		p->camera->angle.z += K_DIR;
// 	else if (key == KEY_E)
// 		p->camera->angle.z -= K_DIR;
// 	ft_paint_scene(p);
// }

// void	look_2(int key, t_rtv *p)
// {
// 	t_vector	start;

// 	start.x = 0;
// 	start.y = 0;
// 	start.z = 0;
// 	if (key == NUM_KEY_2 || key == KEY_3)
// 		start.z -= K_ZOOM;
// 	else if (key == NUM_KEY_8 || key == KEY_2)
// 		start.z += K_ZOOM;
// 	else if (key == NUM_KEY_1 || key == KEY_DOWN)
// 		start.y -= K_ZOOM;
// 	else if (key == NUM_KEY_7 || key == KEY_UP)
// 		start.y += K_ZOOM;
// 	else if (key == NUM_KEY_4 || key == KEY_LEFT)
// 		start.x -= K_ZOOM;
// 	else if (key == NUM_KEY_6 || key == KEY_RIGHT)
// 		start.x += K_ZOOM;
// 	p->camera->start.x += start.x;
// 	p->camera->start.y += start.y;
// 	p->camera->start.z += start.z;
// 	calculate_constant(p, &start);
// 	ft_paint_scene(p);
// }

/*
** New look for mouse camera direction
*/

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
	ft_rotate_vector(&p->camera->angle, &start); // перемещение 
	p->camera->start.x += start.x;
	p->camera->start.y += start.y;
	p->camera->start.z += start.z;
	calculate_constant(p, &start);
	ft_paint_scene(p);
}

void	zoom(int key, t_rtv *p)
{
	int width;
	
	width = p->width;
	if (key == NUM_KEY_PLUS)
		p->fov += K_FOV;
	else if (key == NUM_KEY_MINUS)
		p->fov -= K_FOV;
	if (p->fov <= 0)
		p->fov = K_FOV;
	p->camera->dir.z = p->fov;
	ft_paint_scene(p);
}

void	camera_start(t_rtv *p)
{
	t_vector	start;
	t_vector	tmp;

	start = p->camera->pos;
	p->camera->angle.x = 0;
	p->camera->angle.y = 0;
	p->camera->angle.z = 0;
	tmp = start;
	start = ft_sub_vectors(&start, &p->camera->start);
	p->camera->start = tmp;
	calculate_constant(p, &start);
	p->fov = (double)p->width;
	p->depth_mirror = DEPTH_REFL;
	ft_paint_scene(p);
}

// void	camera_start_2(t_rtv *p)
// {
// 	// t_vector	start;
// 	// t_vector	tmp;
// 	free_memory(p);
// 	init_tab_object(p, p->name_file);
// 	calculate_constant(p, &p->camera->start);
// 	p->fov = (double)p->width;
// 	p->depth_mirror = 1;
// 	ft_paint_scene(p);
// }

void	reflect(t_rtv *p)
{
	p->depth_mirror += 1;
	if (p->depth_mirror == DEPTH)
		p->depth_mirror = 1;
	ft_paint_scene(p);
}

void	aliasing_effects(t_rtv *p)
{
	if (p->aliasing == e_pull)
		p->aliasing = e_push;
	else if (p->aliasing == e_push)
	{
		if (p->samples < MAX_SAMPLE)
			p->samples += 1;
		else
		{
			p->samples = NUM_SAMPLE;
			p->aliasing = e_pull;
		}
	}
	// printf("ALIASING- %d, COUNT- %d\n", p->aliasing, p->samples);
	ft_paint_scene(p);
}

int		key_press(int key, t_rtv *p)
{
	if (key == KEY_ESC)
		close_window(p);
		// exit(0);
	if (key == NUM_KEY_PLUS || key == NUM_KEY_MINUS)
		zoom(key, p);
	if (key == KEY_Q || key == KEY_W || key == KEY_E ||\
		key == KEY_A || key == KEY_S || key == KEY_D ||\
		key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
		look(key, p);
	if (key == KEY_M)
		reflect(p);
	if (key == KEY_N)
		aliasing_effects(p);
	if (key == KEY_O)
		p->filter = 'O';
	//if (key == KEY_T)
		//color_to_anaglyph(p);
		//p->filter = 'S';
	//	cartooning(p);
	//if ( key == KEY_ANSI_S)
	//	p->color_schema = 1;
	// if (key == KEY_D || key == KEY_W || key == KEY_A || key == KEY_S ||\
	// 	key == KEY_Q || key == KEY_E)
	// 	look(key, p);
	// if (key == NUM_KEY_8 || key == NUM_KEY_2 || key == NUM_KEY_4 ||\
	// 	key == NUM_KEY_6 || key == NUM_KEY_1 || key == NUM_KEY_7 ||\
	// 	key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP ||\
	// 	key == KEY_DOWN || key == KEY_2 || key == KEY_3)
	// 	look_2(key, p);
	if (key == KEY_SPACE)
		camera_start(p);
	if (key == KEY_H)
		ft_window_menu(p);
	return (0);
}
