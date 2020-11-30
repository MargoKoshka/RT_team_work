/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:30:42 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:30:43 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Subtract(вычитание векторов V1 из V2 ) two vectors
** and return the resulting vector
*/

t_vector	ft_sub_vectors(t_vector *v1, t_vector *v2)
{
	t_vector result;

	result = (t_vector){v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
	return (result);
}

/*
** Add(сложение векторов) two vectors and return the resulting vector
*/

t_vector	ft_add_vectors(t_vector *v1, t_vector *v2)
{
	t_vector result;

	result = (t_vector){v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
	return (result);
}

/*
** Multiply two vectors(скалярное умножение векторов vectorDot)
** and return the resulting scalar (dot product)
*/

double		ft_vector_scalar(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

/*
** Modul Vectora(len vector) and return the Scalar;
** return (sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2)));
*/

double		ft_vector_modul(t_vector *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

/*
** Проекция vector V1 on vector V2  and return the len vector V1;
** return (sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2)));
*/

double		ft_vector_projection_on_ray(t_vector *v1, t_vector *v2)
{
	return (ft_vector_scalar(v1, v2) / ft_vector_modul(v2));
}
