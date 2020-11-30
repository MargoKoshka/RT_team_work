/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_color2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:31:29 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:34:22 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		apply2(double shade, t_rtv *p, t_cross *in)
{
	t_color		c;
	int			last_color;

	last_color = 0;
	if (p->object[in->id]->texture == PERLIN)
	{
		c = makenoise_perlin(in, p->object[in->id]->perlin_tab, \
		&p->object[in->id]->color);
		last_color = color(&c, shade);
	}
	else if (p->object[in->id]->texture == MARBLE)
	{
		c = makenoise_marble(in, p->object[in->id]->perlin_tab, \
		&p->object[in->id]->color);
		last_color = color(&c, shade);
	}
	else if (p->object[in->id]->texture == CHESS)
	{
		c = ft_get_texture_color(p->object[in->id], in->vec3);
		last_color = color(&c, shade);
	}
	return (last_color);
}

int		apply(double shade, t_rtv *p, t_cross *in)
{
	t_color		c;
	int			last_color;

	last_color = 0;
	if (p->object[in->id]->texture == EARTH ||\
	p->object[in->id]->texture == BLUR ||\
	p->object[in->id]->texture == BRICS ||\
	p->object[in->id]->texture == GRASS)
	{
		c = get_color(p->object[in->id], in);
		last_color = color(&c, shade);
	}
	else if (p->object[in->id]->texture == RAINBOW)
	{
		c = rainbow(p->object[in->id], in, &p->object[in->id]->color);
		last_color = color(&c, shade);
	}
	else if (p->object[in->id]->texture == NO_TEXTURE)
		last_color = color(&p->object[in->id]->color, shade);
	return (last_color);
}

int		ft_local_color(t_rtv *p, t_cross *intersect, t_vector *norm)
{
	double		shade;
	t_color		c;
	int			last_color;

	last_color = 0;
	shade = ft_calculate_lighting(p, intersect, norm);
	if (p->object[intersect->id]->texture == PERLIN || \
	p->object[intersect->id]->texture == MARBLE ||
		p->object[intersect->id]->texture == CHESS)
		last_color = apply2(shade, p, intersect);
	else
		last_color = apply(shade, p, intersect);
	if (p->filter == e_sepia)
		last_color = sepia(last_color);
	if (p->filter == e_wave)
	{
		c = wave_pattern(&intersect->vec3, &p->object[intersect->id]->color);
		last_color = color(&c, shade);
	}
	if (p->filter == e_cartoon)
	{
		c = set_color_cartoon(p->object[intersect->id]->color, shade);
		last_color = color(&c, shade);
	}
	return (last_color);
}
