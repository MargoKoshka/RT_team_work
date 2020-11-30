/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:27:28 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:27:31 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	malloc_lightes_cont(int rez, t_rtv *rt)
{
	if (!(rt->lights = (t_light **)malloc(sizeof(t_light *) * (rez + 1))))
		memory_allocation_error();
	rt->lights[rez] = NULL;
	while (rez > 0)
	{
		rez--;
		if (!(rt->lights[rez] = ft_memalloc(sizeof(t_light ))))
			memory_allocation_error();
		rt->lights[rez]->type = 0;
	}
}

void	malloc_lightes(char *str, int *index, t_rtv *rt)
{
	int rez;
	int counter;

	rez = 0;
	counter = 0;
	if (str[*index] == '[')
	{
		*index = *index + 1;
		while (str[*index] != ']' || counter == 0)
		{
			if ((find_quotes(str, index, "\"type\"\0")))
				rez++;
			*index = *index + 1;
			if (str[*index] == '[')
				counter++;
			if (str[*index] == ']')
				counter--;
		}
		rt->n_lights = rez;
		malloc_lightes_cont(rez, rt);
	}
}

void	malloc_objects_cont(t_rtv *rt, int rez)
{
	if (!(rt->object = (t_object **)malloc(sizeof(t_object *) * (rez + 1))))
		memory_allocation_error();
	rt->object[rez] = NULL;
	while (rez > 0)
	{
		rez--;
		if (!(rt->object[rez] = ft_memalloc(sizeof(t_object))))
			memory_allocation_error();
	}
}

void	malloc_objects(char *str, int *index, t_rtv *rt, int n)
{
	int rez;
	int counter;

	counter = 0;
	rez = 0;
	if (str[*index] == '[')
	{
		*index = *index + 1;
		while (str[*index] != ']' || counter == 0)
		{
			if ((find_quotes(str, index, "\"type\"\0")))
				rez++;
			*index = *index + 1;
			if (str[*index] == '[')
				counter++;
			if (str[*index] == ']')
				counter--;
		}
		rt->n_objects = rez;
		*index = n + 2;
		malloc_objects_cont(rt, rez);
	}
}

void	ft_free_scene(t_rtv *rt)
{
	int	n;

	n = rt->n_lights - 1;
	while (n > -1)
	{
		free(rt->lights[n]);
		n--;
	}
	free(rt->lights);
	n = rt->n_objects - 1;
	while (n > -1)
	{
		free(rt->object[n]);
		n--;
	}
	free(rt->object);
}
