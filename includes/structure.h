/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:06:44 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:06:45 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef float	t_float4 __attribute__((ext_vector_type(4)));

typedef enum
{
	e_pull,
	e_push,
	e_caps,
	e_body
}	t_name;

typedef enum
{
	e_ambient,
	e_point,
	e_direct,
}	t_lights_names;

typedef enum
{
	e_sphere,
	e_plane,
	e_cylindr,
	e_tube,
	e_cone,
	e_hemisphere,
	e_ring,
	e_paraboloid,
}	t_objects_name;

typedef enum
{
	e_no_effect,
	e_sepia,
	e_cartoon,
	e_sereoscopia,
	e_anaglyph,
	e_motion_bler,
	e_wave
}	t_visual_effects;

/*
**The structure OBJECT
*/
typedef enum
{
	NO_TEXTURE,
	EARTH,
	CHESS,
	BRICS,
	BLUR,
	GRASS,
	MARBLE,
	PERLIN,
	RAINBOW
}	t_texture;

typedef struct		s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;

typedef struct		s_uv
{
	double			u;
	double			v;
}					t_uv;

/*
**The vector structure
*/

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

/*
**The ray
*/

typedef struct		s_camera
{
	t_vector		start;
	t_vector		dir;
	t_vector		angle;
	double			pos_cam;
	t_vector		pos;
}					t_camera;

/*
**The light structure
*/

typedef struct		s_light
{
	int				type;
	t_vector		pos;
	t_vector		direction;
	double			intensity;
	t_color			color;
}					t_light;

/*
**The structure for solve quadratic equation
*/

typedef struct		s_discr
{
	t_vector		v2;
	double			a;
	double			b;
	double			c;
	double			k_tan;
	double			pos_n_p;
	double			discr;
	double			sqrt_discr;
	double			d_1;
	double			d_2;
}					t_discr;

/*
**The structure material object
*/

typedef struct		s_material
{
	int				type;
	t_color			color;
	double			k_ambient;
	double			k_diffuse;
	double			k_specular;
	int				specular;
	double			reflection;
	double			refraction;
}					t_material;

typedef struct		s_textura
{
	void			*image;
	char			*name;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
	int				*tab;
}					t_textura;

typedef struct		s_noise
{
	int				tab[512];
	int				i;
	int				cx;
	int				cy;
	int				cz;
	double			u;
	double			v;
	double			w;
	int				a;
	int				b;
	int				aa;
	int				ab;
	int				bb;
	int				ba;
}					t_noise;
/*
**The structure OBJECT
*/

typedef struct		s_object
{
	int				type;
	t_vector		pos;
	t_vector		axis;
	t_vector		angle_n;
	t_discr			discr;
	double			radius;
	double			angle;
	double			len_pos;
	double			pos_cam;
	double			reflection;
	double			refraction;
	double			min;
	double			max;
	double			r_min;
	double			r_max;
	int				check;
	int				specular;
	t_color			color;
	t_texture		texture;
	double			k_paraboloid;
	t_textura		textura;
	int				*perlin_tab;
}					t_object;

typedef struct		s_rtv
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*draw;
	void			*menu_ptr;
	void			*menu_img;
	int				*menu;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
	char			*name_file;
	char			*name_screen;
	char			**scenes;
	int				scene_num;
	int				current_scene;
	t_object		**object;
	t_camera		*camera;
	t_light			*light;
	t_light			**lights;
	double			x0;
	double			y0;
	double			fov;
	int				mouse_key;
	int				mouse_x;
	int				mouse_y;
	int				window_menu;
	int				depth_mirror;
	int				depth_refract;
	int				samples;
	int				selected_obj;
	int				n_lights;
	int				current_light;
	int				n_objects;
	int				current_object;
	int				visual_effect;
	int				*filtered_data;
	void			*filtered_img;
	char			filter;
}					t_rtv;

typedef struct		s_data
{
	t_rtv			*all;
	int				width;
	int				y_start;
	int				y_end;
	int				x;
}					t_data;

typedef struct		s_array
{
	int				local;
	int				reflect;
	int				refract;
}					t_array;

typedef struct		s_cross
{
	double			len;
	int				id;
	int				check;
	t_vector		vec3;
}					t_cross;

typedef struct		s_start
{
	t_vector		start;
	t_vector		ray;
	t_vector		normal;
	t_vector		intersect;
	int				depth;
	int				color;
}					t_start;

typedef struct		s_matrix
{
	double			cos_x;
	double			cos_y;
	double			cos_z;
	double			sin_x;
	double			sin_y;
	double			sin_z;
}					t_matrix;

#endif
