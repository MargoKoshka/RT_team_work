/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytrace_paraboloid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:30:06 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:30:07 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		calculate_a_b_c_paraboloid(t_object *paraboloid, t_vector *ray)
{
	t_vector	oc;
	t_vector	normal;
	double		ray_axis;

	oc = paraboloid->discr.v2;
	normal = paraboloid->axis;
	ray_axis = ft_vector_scalar(ray, &paraboloid->axis);
	paraboloid->discr.a = ft_vector_scalar(ray, ray) - ray_axis * ray_axis;
	paraboloid->discr.b = 2 * (ft_vector_scalar(&oc, ray) -
	(ray_axis * (paraboloid->discr.pos_n_p + 2 * paraboloid->k_paraboloid)));
}

t_cross		ft_intersect_ray_paraboloid(t_object *paraboloid, t_vector *ray)
{
	t_cross		result;
	double		check;

	result.id = NO_INTERSECT;
	calculate_a_b_c_paraboloid(paraboloid, ray);
	ft_solve_quadratic_equation(&paraboloid->discr);
	if (paraboloid->discr.discr < 0.0)
		return (result);
	check = check_intersect(ray,
		&paraboloid->pos, &paraboloid->axis, paraboloid->discr.d_1);
	if (paraboloid->max >= check && check >= paraboloid->min)
	{
		result.id = INTERSECT;
		result.len = paraboloid->discr.d_1;
		return (result);
	}
	check = check_intersect(ray,
		&paraboloid->pos, &paraboloid->axis, paraboloid->discr.d_2);
	if (paraboloid->max >= check && check >= paraboloid->min)
	{
		result.id = INTERSECT;
		result.len = paraboloid->discr.d_2;
	}
	return (result);
}
