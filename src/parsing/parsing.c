/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:28:04 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:28:07 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	camera_parsing(char *str, int *index, t_rtv *rt)
{
	int checker;

	checker = 0;
	rt->camera = ft_memalloc(sizeof(t_camera));
	if (rt->camera == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	while (((checker % 2) == 0) && (checker < 4))
	{
		if (find_quotes(str, index, "\"position\"\0"))
		{
			rt->camera->start = parsing_coordinates(str, index);
			*index += 1;
			checker++;
		}
		else if (find_quotes(str, index, "\"angle_direction\"\0"))
		{
			rt->camera->angle = parsing_angles(str, index);
			checker++;
		}
		else
			file_contents_error();
		checker++;
	}
	rt->camera->dir = (t_vector){0, 0, 1};
	rt->camera->pos = rt->camera->start;
}

void	check_normals(t_rtv *rt)
{
	int n;

	n = 0;
	while (rt->object[n] != NULL)
	{
		if ((rt->object[n]->type == 2) || (rt->object[n]->type == 3) ||\
			(rt->object[n]->type == 4))
			if ((rt->object[n]->axis.x == 0) &&\
			(rt->object[n]->axis.y == 0) && \
			(rt->object[n]->axis.z == 0))
				file_contents_error();
		n++;
	}
}

void	parsing_cont(char *str, int *index, t_rtv *rt)
{
	if (find_quotes(str, index, "\"objects\"\0"))
	{
		*index += 1;
		objects_parsing(str, index, rt);
	}
	else
		file_contents_error();
	check_normals(rt);
}

void	parsing(char *str, t_rtv *rt)
{
	int *index;
	int x;

	x = 1;
	index = &x;
	if (find_quotes(str, index, "\"camera\"\0"))
	{
		*index += 2;
		camera_parsing(str, index, rt);
	}
	else
		file_contents_error();
	if (find_quotes(str, index, "\"lights\"\0"))
	{
		*index += 1;
		lights_parsing(str, index, rt);
	}
	else
		file_contents_error();
	parsing_cont(str, index, rt);
}
