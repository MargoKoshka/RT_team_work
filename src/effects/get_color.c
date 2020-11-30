/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:25:39 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:25:40 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		noise3(double x, double y, double z, int *perlin_tab)
{
	t_noise	perlin;
	int		i;

	i = -1;
	while (++i < 256)
	{
		perlin.tab[i] = perlin_tab[i];
		perlin.tab[256 + i] = perlin_tab[i];
	}
	perlin.cx = (int)floor(x) & 255;
	perlin.cy = (int)floor(y) & 255;
	perlin.cz = (int)floor(z) & 255;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	perlin.u = fade(x);
	perlin.v = fade(y);
	perlin.w = fade(z);
	perlin.a = perlin.tab[perlin.cx] + perlin.cy;
	perlin.aa = perlin.tab[perlin.a] + perlin.cz;
	perlin.ab = perlin.tab[perlin.a + 1] + perlin.cz;
	perlin.b = perlin.tab[perlin.cx + 1] + perlin.cy;
	perlin.ba = perlin.tab[perlin.b] + perlin.cz;
	perlin.bb = perlin.tab[perlin.b + 1] + perlin.cz;
	return (compute_noise(perlin, x, y, z));
}

t_color		makenoise_perlin(t_cross *intersect, int *perlin_tab, t_color *hit)
{
	double	f;
	int		octave;
	t_color	hit1;

	octave = 1;
	f = 0.0;
	while (octave < 10)
	{
		f += (1.0f / octave) *\
		fabsf((float)(noise3(octave * intersect->vec3.x * 0.7,
			octave * intersect->vec3.y * 0.7, octave * intersect->vec3.z *
			0.7, perlin_tab)));
		octave++;
	}
	hit1.blue = (1.0 - f + 0.7 * f) * hit->blue;
	hit1.green = (1.0 - f + 0.7 * f) * hit->green;
	hit1.red = (1.0 - f + 0.7 * f) * hit->red;
	return (hit1);
}

t_color		makenoise_marble(t_cross *intersect, int *perlin_tab, t_color *hit)
{
	double	f;
	int		octave;
	t_color	hit1;

	octave = 1;
	f = 0.0;
	while (octave < 10)
	{
		f += (1.0f / octave) *\
		fabsf((float)(noise3(octave * intersect->vec3.x * 0.7,
			octave * intersect->vec3.y * 0.7, octave * intersect->vec3.z *
			0.7, perlin_tab)));
		octave++;
	}
	f = 1 - sqrt(fabs(sin(2 * PI * f)));
	hit1.blue = (1.0 - f + 0.7 * f) * hit->blue;
	hit1.green = (1.0 - f + 0.7 * f) * hit->green;
	hit1.red = (1.0 - f + 0.7 * f) * hit->red;
	return (hit1);
}
