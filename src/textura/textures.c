/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:31:20 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:31:21 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	get_color_cylindr(t_object *object, t_cross *intersect)
{
	int		i;
	int		column;
	int		row;
	t_color	color;

	i = 0;
	column = 0;
	row = 0;
	get_tex_coord_cylindr(object, &column, &row, intersect);
	i = row * object->textura.size_line + object->textura.bpp / 8 * column;
	color.blue = (int)(unsigned char)object->textura.data[i];
	color.green = (int)(unsigned char)object->textura.data[i + 1];
	color.red = (int)(unsigned char)object->textura.data[i + 2];
	return (color);
}

t_color	get_color(t_object *object, t_cross *intersect)
{
	t_color color;

	if (object->type == e_sphere)
		color = get_color_sphere(object, intersect);
	if (object->type == e_plane)
		color = get_color_plane(object, intersect);
	if (object->type == e_cone)
		color = get_color_cone(object, intersect);
	if (object->type == e_cylindr)
		color = get_color_cylindr(object, intersect);
	return (color);
}

t_color	int_to_rgb(int p)
{
	t_color c;

	c.red = (p >> 16) & 0xFF;
	c.green = (p >> 8) & 0xFF;
	c.blue = (p) & 0xFF;
	return (c);
}

void	anaglyph(t_rtv *scene, int p1, int p2, int p)
{
	t_color c1;
	t_color c2;
	t_color c;

	c1 = int_to_rgb(scene->draw[p1]);
	c2 = int_to_rgb(scene->draw[p2]);
	c = int_to_rgb(scene->draw[p]);
	c.red = c1.red * 0.299 + c1.green * 0.587 + c1.blue * 0.114;
	c.green = 0;
	c.blue = c2.red * 0.299 + c2.green * 0.587 + c2.blue * 0.114;
	scene->filtered_data[p] = ((c.red << 16) | (c.green << 8) | c.blue);
}
