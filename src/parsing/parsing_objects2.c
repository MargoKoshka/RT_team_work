/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:27:58 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:27:59 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		fill_objects_end2(char *str, int *index, t_rtv *rt, int counter)
{
	int count;

	count = 0;
	if (find_quotes(str, index, "\"specularity\"\0"))
	{
		rt->object[rt->current_object]->specular = double_parsing(str, index);
		count = counter + 1;
	}
	else if (find_quotes(str, index, "\"k_paraboloid\"\0"))
	{
		rt->object[rt->current_object]->k_paraboloid = \
		double_parsing(str, index);
		count = counter + 1;
	}
	else if (find_quotes(str, index, "\"min\"\0"))
	{
		rt->object[rt->current_object]->min = double_parsing(str, index);
		count = counter + 1;
	}
	else if (find_quotes(str, index, "\"max\"\0"))
	{
		rt->object[rt->current_object]->max = double_parsing(str, index);
		count = counter + 1;
	}
	return (count);
}

int		fill_objects_end3(char *str, int *index, t_rtv *rt, int counter)
{
	rt->object[rt->current_object]->angle_n = \
	parsing_coordinates(str, index);
	rt->object[rt->current_object]->angle_n.x *= (PI / 180);
	rt->object[rt->current_object]->angle_n.y *= (PI / 180);
	rt->object[rt->current_object]->angle_n.z *= (PI / 180);
	*index = *index + 1;
	counter = counter + 1;
	return (counter);
}

int		fill_objects_end(char *str, int *index, t_rtv *rt, int counter)
{
	int count;

	count = 0;
	if (find_quotes(str, index, "\"angle\"\0"))
	{
		rt->object[rt->current_object]->angle = double_parsing(str, index);
		rt->object[rt->current_object]->angle *= (PI / 180);
		count = counter + 1;
	}
	else if (find_quotes(str, index, "\"axis\"\0"))
	{
		rt->object[rt->current_object]->axis = \
		parsing_coordinates(str, index);
		*index = *index + 1;
		count = counter + 1;
	}
	else if (find_quotes(str, index, "\"axis_angle\"\0"))
		count = fill_objects_end3(str, index, rt, counter);
	else
		count = fill_objects_end2(str, index, rt, counter);
	return (count);
}
