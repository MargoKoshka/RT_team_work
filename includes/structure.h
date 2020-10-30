#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef float	t_float4 __attribute__((ext_vector_type(4)));

typedef enum
{
	e_pull,
	e_push,
	e_sphere,
	e_plane,
	e_cylindr,
	e_tube,
	e_cone,
	e_hemisphere,
	e_ring,
	e_ambient,
	e_point,
	e_direct,
	e_caps,
	e_body
}	t_name;

typedef struct		s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;

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

////////
typedef struct		s_float3
{
	float			x;
	float			y;
	float			z;
}					t_float3;
	
///////
/*
**The light structure
*/

typedef struct		s_light
{
	int				tip;
	t_vector		pos;
	double			intensity;
	t_color			color;
	struct s_light	*next;
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
	int				tip;
	t_color			color;
	double			k_ambient;
	double			k_diffuse;
	double			k_specular;
	int				specular;
	double			reflection;
	double			refraction;
	// struct s_light	*next;
}					t_material;

/*
**The structure OBJECT
*/
enum				e_texture {
	NO_TEXTURE,
	EARTH,
	CHESS
};

/*
typedef struct		s_file_texture
{
	int				*size;
	int				**tab;
}					t_file_texture;
*/
typedef struct s_textura 
{
	void			*image;   // *ptr
	char			*name;   // *path
	char		*data; // int *data
	int				bpp; //bits_per_pixel
	int				size_line;
	int				endian;
	int				width;
	int				height;
	/////
	//double			scale;
	int 			*tab;
}				t_textura;

////////////////////////////////////////////



//////////////////////////////////

/*typedef struct		s_mapping
{
	void			*ptr;
	t_color			*img;
	int				x;
	int				y;
}					t_mapping;

*/

typedef struct		s_object
{
	int				type;
	t_vector		pos;
	// t_vector		pos_start;
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
	unsigned char		*disp_color;
	enum e_texture	texture;
	//unsigned int	txt_size;
	//t_file_texture	file_txt;
	//int				*texture_size;
	//int				**texture_tab;
	//int				col;
	t_textura       textura;
	double			mat[3][3];
	//t_mapping       map;
	//t_file_texture	file_height;
	/* t_material		material;
	t_file_texture	file_txt;
	//t_file_texture	file_txt;*/

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
	// int				num;
	char			*name_file;
	t_object		**object;
	t_camera		*camera;
	t_light			*light;
	double			x0;
	double			y0;
	double			fov;
	int				mouse_key;
	int				mouse_x;
	int				mouse_y;
	int				window_menu;
	int				depth_mirror;
	int				depth_refract;
	int				aliasing;
	int				samples;

	//void			*filtered_img;
	//////
	t_vector				p;
	int				color_schema; // 0 - standart; 1 - sepia;
	float				k;
	char			filter;

	
}					t_rtv;

typedef struct		s_data
{
	t_rtv			*all;
	// t_camera		camera;
	// t_vector		ray;
	int				width;
	// int				height;
	int				y_start;
	int				y_end;
	int				x;
	// double			x0;
	// double			y0;
}					t_data;

typedef struct		s_array
{
	int				local;
	int				reflect;
	int				refract;
}					t_array;

typedef struct		s_cross
{
	// double		d_1;
	// double		d_2;
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

typedef struct		s_2vector
{
	t_vector		ray;
	t_vector		normal;
}					t_2vector;

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
