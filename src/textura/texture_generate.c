/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_generate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:31:16 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:31:17 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	ft_multkv(double k, t_vector v)
{
	t_vector	m;

	m.x = k * v.x;
	m.y = k * v.y;
	m.z = k * v.z;
	return (m);
}

double		ft_dotprod(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		ft_lengthv(t_vector v)
{
	return (sqrt(ft_dotprod(v, v)));
}

int			ft_gen_chess(int countu, int countv, double u, double v)
{
	double		i;
	double		j;

	i = 0;
	j = 0;
	i = (int)(u / (1 / (double)countu));
	j = (int)(v / (1 / (double)countv));
	if ((int)(i + j) % 2 == 0)
		return (1);
	else
		return (0);
}

t_color		ft_map_texture_sphere(t_object *object, t_vector point)
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
	uv.v = 0.5 - asin(npoint.y) / M_PI;
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
