/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:25:43 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:25:44 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		*create_perlinmap(void)
{
	int *permutation;
	int i;

	i = 0;
	permutation = (int *)malloc(sizeof(int) * 256);
	if (permutation)
	{
		while (i < 256)
		{
			permutation[i] = rand() % 256;
			i++;
		}
	}
	else
		return (0);
	return (permutation);
}

double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	u = ((h < 8 || h == 12 || h == 13) ? x : y);
	v = ((h < 4 || h == 12 || h == 13) ? y : z);
	return (((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v));
}

double	compute_noise(t_noise perlin, double x, double y, double z)
{
	return (lerp(perlin.w, lerp(perlin.v, lerp(perlin.u,
		grad(perlin.tab[perlin.aa], x, y, z),
		grad(perlin.tab[perlin.ba], x - 1, y, z)),
		lerp(perlin.u, grad(perlin.tab[perlin.ab], x, y - 1, z),
		grad(perlin.tab[perlin.bb], x - 1, y - 1, z))),
		lerp(perlin.v, lerp(perlin.u,
		grad(perlin.tab[perlin.aa + 1], x, y, z - 1),
		grad(perlin.tab[perlin.ba + 1], x - 1, y, z - 1)),
		lerp(perlin.u, grad(perlin.tab[perlin.ab + 1], x, y - 1, z - 1),
		grad(perlin.tab[perlin.bb + 1], x - 1, y - 1, z - 1)))));
}
