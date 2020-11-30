/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:27:48 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:27:50 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	choose_texture(t_rtv *p, t_object *obj)
{
	int count;

	if (obj->texture == BLUR)
		count = load_texture_blur(p, obj);
	if (obj->texture == EARTH)
		count = load_texture_earth(p, obj);
	if (obj->texture == GRASS)
		count = load_texture_grass(p, obj);
	if (obj->texture == BRICS)
		count = load_texture_wood(p, obj);
}

int		fill_objects_start(char *str, int *index, t_rtv *rt, int counter)
{
	if ((find_quotes(str, index, "\"type\"\0")))
	{
		rt->object[rt->current_object]->type = parsing_object_type(str, index);
		if (str[*index] == ',')
			*index = *index + 1;
		if (str[*index] == '}')
			*index = *index + 2;
		counter++;
	}
	else if (find_quotes(str, index, "\"position\"\0"))
	{
		rt->object[rt->current_object]->pos = parsing_coordinates(str, index);
		counter++;
		*index = *index + 1;
	}
	else if (find_quotes(str, index, "\"texture\"\0"))
	{
		rt->object[rt->current_object]->texture = parsing_texture(str, index);
		counter = counter + 1;
		if (str[*index] == ',')
			*index = *index + 1;
		if (str[*index] == '}')
			*index = *index + 2;
	}
	return (counter);
}

int		fill_objects_middle(char *str, int *index, t_rtv *rt, int counter)
{
	if (find_quotes(str, index, "\"color\"\0"))
	{
		rt->object[rt->current_object]->color = parsing_color(str, index);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"radius\"\0"))
	{
		rt->object[rt->current_object]->radius = double_parsing(str, index);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"reflection\"\0"))
	{
		rt->object[rt->current_object]->reflection = double_parsing(str, index);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"refraction\"\0"))
	{
		rt->object[rt->current_object]->refraction = double_parsing(str, index);
		counter = counter + 1;
	}
	return (counter);
}

int		fill_objects(char *str, int *index, t_rtv *rt, int counter)
{
	int checker;

	checker = counter;
	if ((str[*index + 1] == 't') || (str[*index + 1] == 'p'))
		counter = fill_objects_start(str, index, rt, counter);
	else if ((str[*index + 1] == 'c') || (str[*index + 1] == 'r'))
		counter = fill_objects_middle(str, index, rt, counter);
	else if ((str[*index + 1] == 'a') || (str[*index + 1] == 'n') || \
	(str[*index + 1] == 's') || (str[*index + 1] == 'k') || \
	(str[*index + 1] == 'm'))
		counter = fill_objects_end(str, index, rt, counter);
	else
		file_contents_error();
	if (counter != checker + 1)
		file_contents_error();
	return (counter);
}

void	objects_parsing(char *str, int *index, t_rtv *rt)
{
	int n;
	int counter;

	n = *index;
	counter = 0;
	malloc_objects(str, index, rt, n);
	n = 0;
	while (n < rt->n_objects)
	{
		rt->current_object = n;
		counter = fill_objects(str, index, rt, counter);
		if (counter == 14)
		{
			ft_rotate_vector(&rt->object[n]->angle_n, &rt->object[n]->axis);
			n++;
			counter = 0;
			*index = *index + 1;
		}
	}
}
