/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textura2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:31:03 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:31:04 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		ft_map_texture_plane(t_object *object, t_vector point)
{
	t_color		color;

	color = object->color;
	if (((int)(point.y + CHESS_SUPPORT) / CHESS_DELETION +
		(int)(point.z + CHESS_SUPPORT) / CHESS_DELETION +
		(int)(point.x + CHESS_SUPPORT)) / CHESS_DELETION % 2 == 0)
	{
		color.red /= 2;
		color.green /= 2;
		color.blue /= 2;
	}
	else
	{
		color = object->color;
	}
	return (color);
}

t_color		ft_map_texture_cylindr(t_object *object, t_vector point)
{
	double		theta;
	t_color		color;
	t_uv		uv;
	t_vector	npoint;
	t_vector	tpoint;

	tpoint = ft_sub_vectors(&object->pos, &point);
	npoint = ft_multkv(1 / ft_lengthv(tpoint), tpoint);
	theta = atan2(npoint.x, npoint.z);
	uv.u = 1 - (theta / (2 * M_PI) + 0.5);
	uv.v = point.y - (int)point.y;
	if (ft_gen_chess(16, 8, uv.u, uv.v) == 0)
	{
		color.red = 0;
		color.green = 0;
		color.blue = 0;
	}
	else
		color = object->color;
	return (color);
}

t_color		ft_get_texture_color(t_object *object, t_vector point)
{
	t_color		color;

	if ((object->type == e_sphere) || (object->type == e_cone))
		color = ft_map_texture_sphere(object, point);
	if (object->type == e_plane)
		color = ft_map_texture_plane(object, point);
	if (object->type == e_cylindr)
		color = ft_map_texture_cylindr(object, point);
	return (color);
}
