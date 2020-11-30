/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textura3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:31:08 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:31:09 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vec_normalize(t_vector v)
{
	t_vector	norm;
	float		len;

	len = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}

void		get_tex_coord_sphere(t_object *object, int *column,\
int *row, t_cross *intersect)
{
	float		theta;
	float		u;
	float		v;
	t_vector	npoint;

	npoint = ft_sub_vectors(&object->pos, &intersect->vec3);
	ft_unit_vector(&npoint);
	theta = atan2(npoint.x, npoint.z);
	u = 0.5 + atan2(npoint.y, npoint.x) / M_PI * 0.5;
	v = 0.5 - asin(npoint.z) / M_PI;
	*column = (int)(object->textura.width * u);
	*row = (int)(object->textura.height * v);
}

void		get_tex_coord_plane(t_object *object, int *column,\
int *row, t_cross *intersect)
{
	float		u;
	float		v;
	t_vector	r;

	r = ft_sub_vectors(&object->pos, &intersect->vec3);
	u = r.x * 100;
	v = r.z * 100;
	if (u < 0.0f)
		u *= -1.0f;
	if (v < 0.0f)
		v *= -1.0f;
	*column = (int)u;
	*row = (int)v;
}

void		get_tex_coord_cone(t_object *object, int *column,\
int *row, t_cross *intersect)
{
	float		u;
	float		v;
	t_vector	r;

	r = ft_sub_vectors(&object->pos, &intersect->vec3);
	u = r.x * 400;
	v = r.z * 400;
	if (u < 0.0f)
		u *= -1.0f;
	if (v < 0.0f)
		v *= -1.0f;
	*column = (int)u;
	*row = (int)v;
}
