/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:30:21 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:30:22 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_lights(t_light **lights, int count)
{
	int	n;

	n = 0;
	while (n < count)
	{
		free(lights[n]);
		lights[n] = NULL;
		n += 1;
	}
	free(lights);
	lights = NULL;
}

static void	free_objects(t_object **object, int count)
{
	int	n;

	n = 0;
	while (n < count)
	{
		free(object[n]->perlin_tab);
		free(object[n]);
		object[n] = NULL;
		n += 1;
	}
	free(object);
	object = NULL;
}

void		free_memory(t_rtv *paint)
{
	free(paint->camera);
	paint->camera = NULL;
	if (paint->object != NULL)
		free_objects(paint->object, paint->n_objects);
	if (paint->light != NULL)
		free_lights(paint->lights, paint->n_lights);
}
