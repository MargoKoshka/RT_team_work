/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 00:00:14 by mikhail           #+#    #+#             */
/*   Updated: 2020/10/13 19:50:29 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cone(t_rtv *p, char **tab, int *i)
{
	if (tab == NULL || ft_len_wordtab(tab) != 11)
		ft_exit("Check the Cone parameters. Exit");
	// p->object[*i] = (t_object *)malloc(sizeof(t_object));
	p->object[*i] = ft_memalloc(sizeof(t_object));
	if (p->object[*i] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	p->object[*i]->type = e_cone;
	init_coordinates(&p->object[*i]->pos, tab[1]);
	init_coordinates(&p->object[*i]->axis, tab[2]);
	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
	p->object[*i]->angle = ft_atoi(tab[4]) * PI / 180;
	init_color(&p->object[*i]->color, tab[5]);
	p->object[*i]->specular = ft_atoi(tab[6]);
	p->object[*i]->reflection = ft_atof(tab[7]);
	p->object[*i]->refraction = ft_atof(tab[8]);
	p->object[*i]->min = ft_atof(tab[9]);
	p->object[*i]->max = ft_atof(tab[10]);
	/*if (ft_strcmp(tab[11],  "EARTH") == 0)
		p->object[*i]->texture = EARTH;
	else
		p->object[*i]->texture = NO_TEXTURE;
	
	//
	if (p->object[*i]->texture == EARTH)
		load_texture_to_obj(p, p->object[*i]); // load texture;	
	//
	
	p->object[*i]->txt_size = 100;*/
	ft_rotate_vector(&p->object[*i]->angle_n, &p->object[*i]->axis);
	*i += 1;
}

void	init_cylindr(t_rtv *p, char **tab, int *i)
{
	if (tab == NULL || ft_len_wordtab(tab) != 11)
		ft_exit("Check the Cylindr parameters. Exit");
	p->object[*i] = ft_memalloc(sizeof(t_object));
	if (p->object[*i] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	p->object[*i]->type = e_cylindr;
	init_coordinates(&p->object[*i]->pos, tab[1]);
	init_coordinates(&p->object[*i]->axis, tab[2]);
	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
	p->object[*i]->radius = ft_atof(tab[4]);
	init_color(&p->object[*i]->color, tab[5]);
	p->object[*i]->specular = ft_atoi(tab[6]);
	p->object[*i]->reflection = ft_atof(tab[7]);
	p->object[*i]->refraction = ft_atof(tab[8]);
	p->object[*i]->min = ft_atof(tab[9]);
	p->object[*i]->max = ft_atof(tab[10]);
	/*if (ft_strcmp(tab[11], "EARTH") == 0)
		p->object[*i]->texture = EARTH;
	else
		p->object[*i]->texture = NO_TEXTURE;
	p->object[*i]->txt_size = 200;
	//
	if (p->object[*i]->texture == EARTH)
		load_texture_to_obj(p, p->object[*i]); // load texture;
	
	*/
	ft_rotate_vector(&p->object[*i]->angle_n, &p->object[*i]->axis);
	*i += 1;
}

void	init_plane(t_rtv *p, char **tab, int *i)
{
	if (tab == NULL || ft_len_wordtab(tab) != 10)
		ft_exit("Check the Plane parameters. Exit");
	p->object[*i] = ft_memalloc(sizeof(t_object));
	if (p->object[*i] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	p->object[*i]->type = e_plane;
	p->object[*i]->axis = (t_vector){0, 1, 0};
	init_coordinates(&p->object[*i]->pos, tab[1]);
	// init_coordinates(&p->object[*i]->axis, tab[2]);
	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
	init_color(&p->object[*i]->color, tab[4]);
	p->object[*i]->specular = ft_atoi(tab[5]);
	p->object[*i]->reflection = ft_atof(tab[6]);
	p->object[*i]->refraction = ft_atof(tab[7]);
	p->object[*i]->min = ft_atof(tab[8]);
	p->object[*i]->max = ft_atof(tab[9]);
	//if (ft_strcmp(tab[10], "EARTH") == 0)
	//{
	//p->object[*i]->texture = EARTH;
	
	//else
	//	p->object[*i]->texture = NO_TEXTURE;
	//p->object[*i]->txt_size = 320;
	//p->object[*i]->texture = CHECKERBOARD;
	/*
	if (p->object[*i]->texture == EARTH)
	*/
	//// load texture;
	ft_rotate_vector(&p->object[*i]->angle_n, &p->object[*i]->axis);
	
	*i += 1;
}

void	init_sphere(t_rtv *p, char **tab, int *i)
{
	int	shift;
	int	len_tab;

	len_tab = ft_len_wordtab(tab);
	if (tab == NULL || (len_tab != 7 && len_tab != 10))
		ft_exit("Check the Sphere parameters. Exit");
	p->object[*i] = ft_memalloc(sizeof(t_object));
	if (p->object[*i] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	p->object[*i]->type = e_sphere;
	init_coordinates(&p->object[*i]->pos, tab[1]);
	if (len_tab == 10)
	{
		init_coordinates(&p->object[*i]->axis, tab[2]);
		init_angle_norm(&p->object[*i]->angle_n, tab[3]);
		ft_unit_vector(&p->object[*i]->axis);
		ft_rotate_vector(&p->object[*i]->angle_n, &p->object[*i]->axis);
	}
	shift = (len_tab == 7) ? 0: 2;
	p->object[*i]->radius = ft_atof(tab[2 + shift]);
	init_color(&p->object[*i]->color, tab[3 + shift]);
	p->object[*i]->specular = ft_atoi(tab[4 + shift]);
	p->object[*i]->reflection = ft_atof(tab[5 + shift]);
	p->object[*i]->refraction = ft_atof(tab[6 + shift]);
	if (len_tab == 10)
		p->object[*i]->min = ft_atof(tab[7 + shift]);
	//p->object[*i]->txt_size = 12;
	//if (ft_strcmp(tab[11],  "EARTH") == 0)
	p->object[*i]->texture = CHESS;
	//else
	//	p->object[*i]->texture = NO_TEXTURE; 
	*i += 1;
}

void	init_hemisphere(t_rtv *p, char **tab, int *i)
{
	int	len_tab;

	len_tab = ft_len_wordtab(tab);
	if (tab == NULL || (len_tab != 9 && len_tab != 10))
		ft_exit("Check the HemiSphere parameters. Exit");
	p->object[*i] = ft_memalloc(sizeof(t_object));
	if (p->object[*i] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	p->object[*i]->type = e_hemisphere;
	init_coordinates(&p->object[*i]->pos, tab[1]);
	init_coordinates(&p->object[*i]->axis, tab[2]);
	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
	ft_rotate_vector(&p->object[*i]->angle_n, &p->object[*i]->axis);
	p->object[*i]->radius = ft_atof(tab[4]);
	init_color(&p->object[*i]->color, tab[5]);
	p->object[*i]->specular = ft_atoi(tab[6]);
	p->object[*i]->reflection = ft_atof(tab[7]);
	p->object[*i]->refraction = ft_atof(tab[8]);
	if (len_tab == 10)
		p->object[*i]->min = ft_atof(tab[9]);
	ft_unit_vector(&p->object[*i]->axis);
	*i += 1;
}

// void	init_ring(t_rtv *p, char **tab, int *i)
// {
// 	int	len_tab;

// 	len_tab = ft_len_wordtab(tab);
// 	if (tab == NULL || len_tab != 10)
// 		ft_exit("Check the Ring parameters. Exit");
// 	p->object[*i] = ft_memalloc(sizeof(t_object));
// 	if (p->object[*i] == NULL)
// 		ft_exit(ERR_CREAT_TO_ARR);
// 	p->object[*i]->tip = e_ring;
// 	init_coordinates(&p->object[*i]->pos, tab[1]);
// 	init_coordinates(&p->object[*i]->axis, tab[2]);
// 	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
// 	ft_rotate_vector(&p->object[*i]->angle_n, &p->object[*i]->axis);
// 	p->object[*i]->radius = ft_atof(tab[4]);
// 	init_color(&p->object[*i]->color, tab[5]);
// 	p->object[*i]->specular = ft_atoi(tab[6]);
// 	p->object[*i]->reflection = ft_atof(tab[7]);
// 	p->object[*i]->refraction = ft_atof(tab[8]);
// 	p->object[*i]->hight = ft_atof(tab[9]);
// 	*i += 1;
// }

void	init_camera(t_rtv *p, char **tab)
{
	if (tab == NULL || ft_len_wordtab(tab) != 4)
		ft_exit("Check the Camera parameters. Exit");
	p->camera = ft_memalloc(sizeof(t_camera));
	if (p->camera == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	init_coordinates(&p->camera->start, tab[1]);
	init_coordinates(&p->camera->dir, tab[2]);
	init_angle_norm(&p->camera->angle, tab[3]);
	p->camera->pos = p->camera->start;
}
