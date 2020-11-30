/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:27:41 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:27:44 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		move(char *str, int *index, int counter)
{
	if (str[*index] == ',')
		*index = *index + 1;
	if (str[*index] == '{')
		*index = *index + 1;
	counter++;
	return (counter);
}

int		move_type(char *str, int *index, int counter)
{
	if (str[*index] == '}')
		*index = *index + 3;
	else if (str[*index] == ',')
		*index = *index + 1;
	counter++;
	return (counter);
}

int		find_option1(char *str, int *index, int counter, t_rtv *rt)
{
	if (find_quotes(str, index, "\"intensity\"\0"))
	{
		intensity_parsing(str, index, rt, rt->current_light);
		counter++;
	}
	else if (find_quotes(str, index, "\"color\"\0"))
	{
		rt->lights[rt->current_light]->color = parsing_color(str, index);
		counter++;
	}
	else
		file_contents_error();
	return (counter);
}

int		find_option(char *str, int *index, int counter, t_rtv *rt)
{
	int count;

	count = 0;
	if ((find_quotes(str, index, "\"type\"\0")))
	{
		rt->lights[rt->current_light]->type = parsing_type(str, index);
		count = move_type(str, index, counter);
	}
	else if (find_quotes(str, index, "\"position\"\0"))
	{
		rt->lights[rt->current_light]->pos = \
		parsing_coordinates(str, index);
		count = move(str, index, counter);
	}
	else if (find_quotes(str, index, "\"direction\"\0"))
	{
		rt->lights[rt->current_light]->direction = \
		parsing_coordinates(str, index);
		count = move(str, index, counter);
	}
	else
		count = find_option1(str, index, counter, rt);
	return (count);
}

void	lights_parsing(char *str, int *index, t_rtv *rt)
{
	int n;
	int i;
	int counter;

	n = *index;
	i = *index;
	counter = 0;
	malloc_lightes(str, index, rt);
	*index = n + 2;
	n = 0;
	while (n < rt->n_lights)
	{
		rt->current_light = n;
		if ((counter == 0) && (n > 0))
		{
			*index = *index + 1;
		}
		counter = find_option(str, index, counter, rt);
		if (counter == 5)
		{
			n++;
			counter = 0;
		}
	}
}
