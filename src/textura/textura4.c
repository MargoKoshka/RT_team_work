/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textura4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:31:12 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:31:13 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	get_color_cone(t_object *object, t_cross *intersect)
{
	int			i;
	int			column;
	int			row;
	t_color		color;

	i = 0;
	column = 0;
	row = 0;
	get_tex_coord_cone(object, &column, &row, intersect);
	i = row * object->textura.size_line + object->textura.bpp / 8 * column;
	color.blue = (int)(unsigned char)object->textura.data[i];
	color.green = (int)(unsigned char)object->textura.data[i + 1];
	color.red = (int)(unsigned char)object->textura.data[i + 2];
	return (color);
}

t_color	get_color_plane(t_object *object, t_cross *intersect)
{
	int			i;
	int			column;
	int			row;
	t_color		color;

	i = 0;
	column = 0;
	row = 0;
	get_tex_coord_plane(object, &column, &row, intersect);
	i = row * object->textura.size_line + object->textura.bpp / 8 * column;
	color.blue = (int)(unsigned char)object->textura.data[i];
	color.green = (int)(unsigned char)object->textura.data[i + 1];
	color.red = (int)(unsigned char)object->textura.data[i + 2];
	return (color);
}

t_color	get_color_sphere(t_object *object, t_cross *intersect)
{
	int			i;
	int			column;
	int			row;
	t_color		color;

	i = 0;
	column = 0;
	row = 0;
	get_tex_coord_sphere(object, &column, &row, intersect);
	i = row * object->textura.size_line + object->textura.bpp / 8 * column;
	color.blue = (int)(unsigned char)object->textura.data[i];
	color.green = (int)(unsigned char)object->textura.data[i + 1];
	color.red = (int)(unsigned char)object->textura.data[i + 2];
	return (color);
}

void	get_tex_coord_cylindr(t_object *object, int *column, \
int *row, t_cross *intersect)
{
	float		theta;
	float		u;
	float		v;
	t_vector	npoint;
	t_vector	tpoint;

	tpoint = ft_sub_vectors(&object->pos, &intersect->vec3);
	npoint = ft_multkv(1 / ft_lengthv(tpoint), tpoint);
	theta = atan2(npoint.x, npoint.z);
	u = 0.5 + atan2(npoint.z, npoint.x) / M_PI * 0.5;
	v = 0.5 - asin(npoint.y) / M_PI;
	*column = (int)(object->textura.width * u);
	*row = (int)(object->textura.height * v);
}
