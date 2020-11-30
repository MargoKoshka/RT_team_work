/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:05:02 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:05:24 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structure.h"

/*
** read_file.c
*/
void		read_file(t_rtv *rt, char *file_name);

/*
** check_file.c
*/
void		check_file(char *str);

/*
** errors.c
*/
void		memory_allocation_error(void);
void		read_error(void);
void		file_error(void);
void		empty_file_error(char *str, char *buf);
void		file_contents_error(void);

/*
** malloc_free.c
*/
void		malloc_lightes(char *str, int *index, t_rtv *rt);
void		malloc_objects(char *str, int *index, t_rtv *rt, int n);
void		ft_free_scene(t_rtv *rt);

/*
** parsing.c
*/
void		parsing(char *str, t_rtv *rt);
void		camera_parsing(char *str, int *index, t_rtv *paint);

/*
** parsing_lights.c
*/
void		lights_parsing(char *str, int *index, t_rtv *rt);

/*
** parsing_objects.c
*/
void		objects_parsing(char *str, int *index, t_rtv *rt);

/*
** tools.c
*/
int			find_quotes(char *str, int *index, char *mask);
t_vector	parsing_coordinates(char *str, int *index);
t_vector	parsing_angles(char *str, int *index);
double		rt_atof(const char *str);

/*
** tools_lights.c
*/
int			parsing_type(char *str, int *index);
void		intensity_parsing(char *str, int *index, t_rtv *rt, int n);

/*
** tools_objects.c
*/
t_color		parsing_color(char *str, int *index);
int			parsing_object_type(char *str, int *index);
double		double_parsing(char *str, int *index);
int			int_parsing(char *str, int *index);
int			parsing_texture(char *str, int *index);

/*
** tools_objects.c
*/
int			count_spaces(char *str);

#endif
