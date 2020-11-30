/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anaglyph_mb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:25:26 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:25:27 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	motion_bler(t_rtv *scene, int p1, int p2, int p)
{
	t_color c1;
	t_color c2;
	t_color c;

	c1 = int_to_rgb(scene->draw[p1]);
	c2 = int_to_rgb(scene->draw[p2]);
	c = int_to_rgb(scene->draw[p]);
	c.red = (c1.red / 3 + c.red / 3 + c2.red / 3);
	c.green = (c1.green / 3 + c.green / 3 + c2.green / 3);
	c.blue = (c1.blue / 3 + c.blue / 3 + c2.blue / 3);
	scene->filtered_data[p] = ((c.red << 16) | (c.green << 8) | c.blue);
}

void	motion_bluer(t_rtv *s)
{
	int		i;
	int		j;
	int		p;
	int		p1;
	int		p2;

	i = -1;
	j = -1;
	while (++j < s->height)
	{
		while (++i < s->width)
		{
			p = s->width * j + i;
			p1 = s->width * j + i - 3;
			p2 = s->width * j + i + 3;
			if ((i - 3) < 0)
				p1 = p;
			if ((i + 3) > s->width - 1)
				p2 = p;
			motion_bler(s, p1, p2, p);
		}
		i = -1;
	}
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->filtered_img, 0, 0);
}

void	color_to_anaglyph(t_rtv *scene)
{
	int		i;
	int		j;
	int		p;
	int		p1;
	int		p2;

	i = -1;
	j = -1;
	while (++j < scene->height)
	{
		while (++i < scene->width)
		{
			p = scene->width * j + i;
			p1 = scene->width * j + i - 3;
			p2 = scene->width * j + i + 3;
			if ((i - 3) < 0)
				p1 = p;
			if ((i + 3) > scene->width - 1)
				p2 = p;
			anaglyph(scene, p1, p2, p);
		}
		i = -1;
	}
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, \
	scene->filtered_img, 0, 0);
}
