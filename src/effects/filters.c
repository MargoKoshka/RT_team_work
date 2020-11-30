/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:25:31 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:25:32 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	integer_to_rgb(int clr)
{
	return (t_color){(clr >> 16) & 255, (clr >> 8) & 255, clr & 255};
}

t_color			wave_pattern(t_vector *uv, t_color *mat)
{
	double u;
	double v;
	double sines;

	u = uv->x * 100;
	v = uv->y * 100;
	sines = sin(u * 1.51 + v * 0.502);
	if (sines < 0)
		return (*mat);
	else
		return (integer_to_rgb(COLOR_BG_BL));
}

t_color			set_color_cartoon(t_color color, double light)
{
	t_color c;

	if (light < 0.3)
		light = 0.3;
	else if (light < 0.7)
		light = 0.7;
	else
		light = 1.0;
	c.red = color.red * light;
	c.green = color.green * light;
	c.blue = color.blue * light;
	return (c);
}
