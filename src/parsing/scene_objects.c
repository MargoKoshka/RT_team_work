/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 00:19:06 by mikhail           #+#    #+#             */
/*   Updated: 2020/10/16 20:59:37 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// int		how_many_object(char *src)
int		how_many_object(int fd)
{
	int		count;
	// int		fd;
	char	*line;
	char	*word;
	char	*name_obj;

	line = NULL;
	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		// while (*line == ' ')
		// 	line += 1;
		if (line != NULL)
		{
			line = ft_strtrim(line);
			if ((word = ft_strchr(line, '\t')) != NULL)
			{
				name_obj = ft_strsub(line, 0, word - line);
				if (ft_strcmp(name_obj, "Sphere") == 0 ||
					ft_strcmp(name_obj, "Plane") == 0 ||
					ft_strcmp(name_obj, "Cylindr") == 0 ||
					ft_strcmp(name_obj, "Cone") == 0 ||
					ft_strcmp(name_obj, "HemiSphere") == 0 ||
					ft_strcmp(name_obj, "Ring") == 0 ||
					ft_strcmp(name_obj, "Tube") == 0)
					count += 1;
				free(line);
				free(name_obj);
			}
		}
	}
	close(fd);
	return (count);
}

void	add_object_to_tab(t_rtv *paint, char **tab, int *i)
{
	if (ft_strcmp(tab[0], "Sphere") == 0)
		init_sphere(paint, tab, i);
	else if (ft_strcmp(tab[0], "Plane") == 0)
		init_plane(paint, tab, i);
	else if (ft_strcmp(tab[0], "Cylindr") == 0)
		init_cylindr(paint, tab, i);
	else if (ft_strcmp(tab[0], "Cone") == 0)
		init_cone(paint, tab, i);
	else if (ft_strcmp(tab[0], "HemiSphere") == 0)
		init_hemisphere(paint, tab, i);
	else if (ft_strcmp(tab[0], "Ring") == 0)
	{
		init_sphere(paint, tab, i);
		paint->object[*i - 1]->type = e_ring;
	}
	else if (ft_strcmp(tab[0], "Tube") == 0)
	{
		init_cylindr(paint, tab, i);
		paint->object[*i - 1]->type = e_tube;
	}
}

void	init_tab_object(t_rtv *paint, char *src)
{
	int		i;
	int		fd;
	char	*line;
	char	**tab;

	line = NULL;
	i = 0;
	if ((fd = open(src, O_RDONLY)) <= 0)
		ft_exit(ERR_FILE_OPEN);
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, '\t');
		if (tab != NULL && *tab != NULL)
		{
			if (ft_strcmp(tab[0], "Light") == 0)
				paint->light = init_light(paint->light, tab);
			if (ft_strcmp(tab[0], "Camera") == 0)
				init_camera(paint, tab);
			if (ft_strcmp(tab[0], "Window") == 0)
				init_window(paint, tab);
			else
				add_object_to_tab(paint, tab, &i);
			ft_free_wordtab(tab);
			free(line);
		}
	}
	paint->object[i] = NULL;
	close(fd);
	if (!paint->width || !paint->height)
		ft_exit("No inicialization window. Exit");
	if (paint->camera == NULL)
		ft_exit("No camera. Exit");
	if (paint->light == NULL)
		ft_exit("No light. Exit");
}
