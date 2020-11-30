/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:30:57 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:30:58 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		load_texture_blur(t_rtv *p, t_object *obj)
{
	obj->textura.name = "xpm/blur.xpm";
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr,\
	obj->textura.name, &obj->textura.width, &obj->textura.height);
	obj->textura.data = mlx_get_data_addr(obj->textura.image,\
	&obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	return (1);
}

int		load_texture_earth(t_rtv *p, t_object *obj)
{
	obj->textura.name = "xpm/earth.xpm";
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr,\
	obj->textura.name, &obj->textura.width, &obj->textura.height);
	obj->textura.data = mlx_get_data_addr(obj->textura.image,\
	&obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	return (1);
}

int		load_texture_grass(t_rtv *p, t_object *obj)
{
	obj->textura.name = "xpm/Grass.xpm";
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr,\
	obj->textura.name, &obj->textura.width, &obj->textura.height);
	obj->textura.data = mlx_get_data_addr(obj->textura.image,\
	&obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	return (1);
}

int		load_texture_wood(t_rtv *p, t_object *obj)
{
	obj->textura.name = "xpm/wood.xpm";
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr,
	obj->textura.name, &obj->textura.width, &obj->textura.height);
	obj->textura.data = mlx_get_data_addr(obj->textura.image,\
	&obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	return (1);
}
