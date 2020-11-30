/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:25:47 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:25:48 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			color_limits(int col)
{
	if (col < 0)
		return (0);
	if (col > 255)
		return (255);
	else
		return (col);
}

t_vector	hextorgb(int hex)
{
	t_vector rgb;

	rgb.x = (int)((hex / (0x100 * 0x100)) % 0x100);
	rgb.y = (int)((hex / 0x100) % 0x100);
	rgb.z = (int)(hex % 0x100);
	return (rgb);
}

int			sepia(int color)
{
	t_vector rgb;
	t_vector sepiargb;

	rgb = hextorgb(color);
	sepiargb.x = ((double)(rgb.x * 393) + (rgb.y * 769) + (rgb.z * 189)) / 1000;
	sepiargb.y = ((double)(rgb.x * 349) + (rgb.y * 686) + (rgb.z * 168)) / 1000;
	sepiargb.z = ((double)(rgb.x * 272) + (rgb.y * 534) + (rgb.z * 131)) / 1000;
	return (color_limits(sepiargb.x) * 256 * 256 +
	color_limits(sepiargb.y) * 256 + color_limits(sepiargb.z));
}
