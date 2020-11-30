/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_color3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:30:53 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:42:02 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		rb_sphere(t_object *obj, t_cross *inter)
{
	float		theta;
	float		u;
	t_vector	npoint;

	npoint = ft_sub_vectors(&obj->pos, &inter->vec3);
	ft_unit_vector(&npoint);
	theta = atan2(npoint.x, npoint.z);
	u = 0.5 + atan2(npoint.y, npoint.x) / M_PI * 0.5;
	return ((u) * 1530);
}

static int		rb_plane(t_object *obj, t_cross *inter)
{
	float		u;
	float		v;
	t_vector	r;

	r = ft_sub_vectors(&obj->pos, &inter->vec3);
	u = r.x * 100;
	v = r.z * 100;
	if (u < 0.0f)
		u *= -1.0f;
	if (v < 0.0f)
		v *= -1.0f;
	return (((int)(u / 0.5) % 1530));
}

static int		rb_cyl_cone(t_object *obj, t_cross *inter)
{
	float		theta;
	float		u;
	t_vector	npoint;

	npoint = ft_sub_vectors(&obj->pos, &inter->vec3);
	ft_unit_vector(&npoint);
	theta = atan2(npoint.x, npoint.z);
	u = 0.5 + atan2(npoint.y, npoint.x) / M_PI * 0.5;
	return ((u) * 1530);
}

static t_color	rainbow2(t_color ret, double len)
{
	if (len < 765)
	{
		ret.red = 0;
		ret.green = 255;
		ret.blue = len - 510;
	}
	else if (len < 1020)
	{
		ret.red = 0;
		ret.green = 1020 - len;
		ret.blue = 255;
	}
	else if (len < 1275)
	{
		ret.red = len - 1020;
		ret.green = 0;
		ret.blue = 255;
	}
	else
	{
		ret.red = 255;
		ret.green = 0;
		ret.blue = 1530 - len;
	}
	return (ret);
}

t_color			rainbow(t_object *obj, t_cross *inter, t_color *color)
{
	t_color		ret;
	int			len;

	len = 0;
	if (obj->type == e_sphere)
		len = rb_sphere(obj, inter);
	else if (obj->type == e_plane)
		len = rb_plane(obj, inter);
	else if (obj->type == e_cylindr || obj->type == e_cone)
		len = rb_cyl_cone(obj, inter);
	ret = *color;
	if (len < 255)
	{
		ret.red = 255;
		ret.green = len;
		ret.blue = 0;
	}
	else if (len < 510)
	{
		ret.red = 510 - len;
		ret.green = 255;
		ret.blue = 0;
	}
	return (len < 510 ? ret : rainbow2(ret, len));
}
