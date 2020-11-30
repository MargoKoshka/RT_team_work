/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_standard_methods.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:30:29 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 12:01:23 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		close_window(void *param)
{
	t_rtv	*paint;

	paint = (t_rtv *)param;
	free_memory(paint);
	exit(0);
}

void	ft_exit(void *param)
{
	char *str;

	str = (char *)param;
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(1);
}

int		expose_hook(t_rtv *p)
{
	mlx_do_sync(p->mlx_ptr);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 30, 0xF8F924,
					"Menu, navigation - key H");
	print_navigation(p);
	if (p->window_menu == OPEN)
		ft_drawing_menu(p);
	if (p->filter == e_anaglyph)
		color_to_anaglyph(p);
	if (p->filter == e_motion_bler)
		motion_bluer(p);
	return (1);
}

void	ft_hook_operation(t_rtv *paint)
{
	mlx_hook(paint->win_ptr, KEY_PRESS, (1L << 0), key_press, paint);
	mlx_hook(paint->win_ptr, BUTTON_PRESS, (1L << 2), mouse_press, paint);
	mlx_hook(paint->win_ptr, BUTTON_RELEASE, (1L << 3), mouse_release, paint);
	mlx_hook(paint->win_ptr, MOTION_NOTIFY, (1L << 6), mouse_movement, paint);
	mlx_hook(paint->win_ptr, DESTROY_NOTIFY, (1L << 17), close_window, paint);
	mlx_hook(paint->win_ptr, EXPOSE, (1L << 15), expose_hook, paint);
	mlx_loop(paint->mlx_ptr);
}

void	ft_put_pixel(t_rtv *paint, int x, int y, int color)
{
	paint->draw[x + y * paint->width] = color;
}
