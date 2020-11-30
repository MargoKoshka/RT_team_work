/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:32:28 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 12:02:00 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_navigation(t_rtv *p)
{
	char	*str;
	char	*coord;

	coord = ft_itoa(p->fov);
	str = ft_strjoin(STR2, coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 50, COLOR_STR, str);
	free(coord);
	free(str);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 70, COLOR_STR, STR1);
	coord = ft_itoa(p->camera->start.x);
	str = ft_strjoin("X = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 90, COLOR_STR, str);
	free(coord);
	free(str);
	coord = ft_itoa(p->camera->start.y);
	str = ft_strjoin("Y = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 110, COLOR_STR, str);
	free(coord);
	free(str);
	coord = ft_itoa(p->camera->start.z);
	str = ft_strjoin("Z = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 130, COLOR_STR, str);
	free(coord);
	free(str);
}

void	ft_init_texture(t_rtv *p)
{
	int count;

	count = 0;
	while (count < p->n_objects)
	{
		if (p->object[count]->texture == PERLIN ||\
		p->object[count]->texture == MARBLE)
			p->object[count]->perlin_tab = create_perlinmap();
		if (p->object[count]->texture == BLUR ||\
		p->object[count]->texture == BRICS ||\
		p->object[count]->texture == EARTH ||\
		p->object[count]->texture == GRASS)
			choose_texture(p, p->object[count]);
		count++;
	}
}

void	ft_mlx_init(t_rtv *p)
{
	p->win_ptr = mlx_new_window(p->mlx_ptr, p->width, p->height, p->name_file);
	p->img_ptr = mlx_new_image(p->mlx_ptr, p->width, p->height);
	p->draw =
	(int *)mlx_get_data_addr(p->img_ptr, &p->bpp, &p->size_line, &p->endian);
	p->filtered_img = mlx_new_image(p->mlx_ptr, p->width, p->height);
	p->filtered_data = (int *)mlx_get_data_addr(p->filtered_img,\
	&p->bpp, &p->size_line, &p->endian);
	p->filter = e_no_effect;
}

void	ft_paint_scene(t_rtv *paint)
{
	ft_multi_thread_paint(paint);
	expose_hook(paint);
}

int		main(int argc, char **argv)
{
	t_rtv	paint;

	if (argc < 2)
		ft_exit(ERR_USAGE);
	paint.scenes = argv;
	paint.scene_num = argc - 1;
	paint.current_scene = 1;
	paint.name_file = argv[1];
	read_file(&paint, argv[1]);
	paint.mlx_ptr = mlx_init();
	ft_init_configuration(&paint);
	ft_init_texture(&paint);
	calculate_constant(&paint, &paint.camera->start);
	ft_paint_scene(&paint);
	ft_hook_operation(&paint);
	return (0);
}
