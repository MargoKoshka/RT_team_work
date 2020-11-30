/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:32:17 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 12:45:20 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_drawing_fon(t_rtv *p)
{
	int	x;
	int	y;

	y = 0;
	while (y < p->height)
	{
		x = 0;
		while (x < W_MENU)
		{
			p->menu[x + y * W_MENU] = COLOR_BG_BLU;
			x += 1;
		}
		y += 1;
	}
	mlx_put_image_to_window(p->mlx_ptr, p->menu_ptr, p->menu_img, 0, 0);
}

static void	print_navigation_menu(t_rtv *p)
{
	char	*str;
	char	*coord;

	coord = ft_itoa(p->fov);
	str = ft_strjoin(STR2, coord);
	mlx_string_put(p->mlx_ptr, p->menu_ptr, 20, 30, COLOR_STR, str);
	free(coord);
	free(str);
	mlx_string_put(p->mlx_ptr, p->menu_ptr, 20, 50, COLOR_STR, STR1);
	coord = ft_itoa(p->camera->start.x);
	str = ft_strjoin("X = ", coord);
	mlx_string_put(p->mlx_ptr, p->menu_ptr, 20, 70, COLOR_STR, str);
	free(coord);
	free(str);
	coord = ft_itoa(p->camera->start.y);
	str = ft_strjoin("Y = ", coord);
	mlx_string_put(p->mlx_ptr, p->menu_ptr, 20, 90, COLOR_STR, str);
	free(coord);
	free(str);
	coord = ft_itoa(p->camera->start.z);
	str = ft_strjoin("Z = ", coord);
	mlx_string_put(p->mlx_ptr, p->menu_ptr, 20, 110, COLOR_STR, str);
	free(coord);
	free(str);
}

static void	print_navigation_menu_2(t_rtv *p)
{
	char	*str;
	char	*coord;

	coord = ft_itoa(p->samples);
	str = ft_strjoin("Count samples: ", coord);
	mlx_string_put(p->mlx_ptr, p->menu_ptr, 20, 300, COLOR_STR, str);
	free(coord);
	free(str);
}

static void	print_instructions(t_rtv *p)
{
	mlx_string_put(p->mlx_ptr, p->menu_ptr, 120, 90, COLOR_STR, \
	"Q,E - move Y");
	mlx_string_put(p->mlx_ptr, p->menu_ptr, 120, 70, COLOR_STR, \
	"A,D - move X");
	mlx_string_put(p->mlx_ptr, p->menu_ptr, 120, 110, COLOR_STR, \
	"W,S - move Z");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 130, COLOR_STR, "Arrows - up, down, right, left");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 170, COLOR_STR, "Camera direction: ");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 190, COLOR_STR, "press left mouse key to change");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 330, COLOR_STR, "key N - aliasing");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 350, COLOR_STR, "key T - wave");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 370, COLOR_STR, "key Y - anaglyph");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 390, COLOR_STR, "key U - motion blur");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 410, COLOR_STR, "key I - cartoon effect");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 430, COLOR_STR, "key O - sepia effect");
}

void		ft_drawing_menu(t_rtv *p)
{
	p->menu_img = mlx_new_image(p->mlx_ptr, W_MENU, p->height);
	p->menu = (int *)mlx_get_data_addr(p->menu_img, &p->bpp, \
				&p->size_line, &p->endian);
	ft_drawing_fon(p);
	print_navigation_menu(p);
	print_navigation_menu_2(p);
	print_instructions(p);
	print_instructions_for_obj(p);
}
