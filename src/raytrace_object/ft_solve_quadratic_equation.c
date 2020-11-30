/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_quadratic_equation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:30:14 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:30:15 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_swap_double(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	ft_solve_discriminant(t_discr *discr)
{
	discr->discr = (double)(discr->b * discr->b - 4 * discr->a * discr->c);
}

void		ft_solve_quadratic_equation(t_discr *discr)
{
	discr->d_1 = NO_INTERSECT;
	discr->d_2 = NO_INTERSECT;
	ft_solve_discriminant(discr);
	if (discr->discr >= 0)
	{
		discr->sqrt_discr = sqrtf(discr->discr);
		discr->a = 2 * discr->a;
		discr->d_1 = (-discr->b - discr->sqrt_discr) / discr->a;
		discr->d_2 = (-discr->b + discr->sqrt_discr) / discr->a;
		if (discr->d_1 >= 0.001f && discr->d_2 >= 0.001f)
		{
			if (discr->d_1 > discr->d_2)
				ft_swap_double(&discr->d_1, &discr->d_2);
		}
		if (discr->d_1 < 0.001f && discr->d_2 > 0.001f)
			ft_swap_double(&discr->d_1, &discr->d_2);
	}
}

double		ft_solve_quadratic_equation_old(t_discr *discr)
{
	ft_solve_discriminant(discr);
	if (discr->discr < 0)
		return (NO_INTERSECT);
	discr->sqrt_discr = sqrtf(discr->discr);
	discr->a = 2 * discr->a;
	discr->d_1 = (-discr->b - discr->sqrt_discr) / discr->a;
	discr->d_2 = (-discr->b + discr->sqrt_discr) / discr->a;
	if (discr->d_1 > 0.001f && discr->d_2 > 0.001f)
	{
		discr->d_1 = (discr->d_1 <= discr->d_2) ? discr->d_1 : discr->d_2;
		return (discr->d_1);
	}
	else if (discr->d_1 > 0.001f && discr->d_2 < 0)
		return (discr->d_1);
	else if (discr->d_1 < 0.001f && discr->d_2 > 0.001f)
		return (discr->d_2);
	return (NO_INTERSECT);
}
