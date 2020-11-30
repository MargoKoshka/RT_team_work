/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_menu2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:32:21 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 13:53:36 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_window_menu(t_rtv *p)
{
	if (p->window_menu == CLOSED)
	{
		p->menu_ptr = mlx_new_window(p->mlx_ptr, W_MENU, p->height, "MENU");
		ft_drawing_menu(p);
		p->window_menu = OPEN;
		mlx_hook(p->menu_ptr, 2, (1L << 0), key_press, p);
		mlx_hook(p->menu_ptr, 17, (1L << 0), close_window, p);
	}
	else if (p->window_menu == OPEN)
	{
		p->window_menu = CLOSED;
		mlx_destroy_window(p->mlx_ptr, p->menu_ptr);
	}
}

void	ft_init_configuration(t_rtv *p)
{
	p->width = WIDHT;
	p->height = HIGHT;
	p->x0 = (p->width - 1) / 2.0;
	p->y0 = (p->height - 1) / 2.0;
	p->fov = (double)p->width;
	p->mouse_key = 0;
	p->mouse_x = 0;
	p->mouse_y = 0;
	p->window_menu = CLOSED;
	p->samples = MIN_SAMPLE;
	p->depth_mirror = DEPTH_REFL;
	p->depth_refract = DEPTH_REFR;
	p->camera->dir.z = p->fov;
	p->selected_obj = NO_INTERSECT;
	p->visual_effect = e_pull;
	ft_mlx_init(p);
}

void	print_instructions_for_obj(t_rtv *p)
{
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 470, COLOR_STR, "Press right key-mouse");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 490, COLOR_STR, "to choose the figure");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 510, COLOR_STR, "Move figure (use side key boarg):");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 530, COLOR_STR, "Up/Down - 7/1");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 550, COLOR_STR, "Left/Right - 4/6");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 570, COLOR_STR, "Backward/Forward - 8/2");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 230, COLOR_STR, "Whitespace - ");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 250, COLOR_STR, "Go back to the original version");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 610, COLOR_STR, "Printscreen - P");
}
