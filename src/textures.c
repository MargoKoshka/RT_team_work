#include "rtv1.h"
#include <stdio.h>
/*
int		*color_tab(char *imgstr, int size, int size1)
{
	int		*color_tab;
	int		total_size;
	int		i;

	i = 0;
	total_size = size * size1;
	color_tab = (int *)malloc(sizeof(int*) * total_size);
	while (i < total_size)
	{
		color_tab[i] = imgstr[i];
		i++;
	}
	return (color_tab);
}*/
/*
int		**color_tab(int *imgstr, int size, int size1)
{
	int		**color_tab;
	int		x;
	int		y;
	int		i;

	y = -1;
	i = 0;
	if (!(color_tab = (int **)malloc(sizeof(int*) * size1 * 2)) || !imgstr)
		return (NULL);
	while (++y < size1)
	{
		if (!(color_tab[y] = (int *)malloc(sizeof(int) * size * 2)))
		{
			//free_color_tab(color_tab, y);
			return (NULL);
		}
		x = -1;
		while (++x < size)
		{
			color_tab[y][x] = imgstr[i];
			i++;
		}
	}
	return (color_tab);
}
*/
int		load_texture_blur(t_rtv *p,t_object *obj)
{
	obj->textura.name = "xpm/blur.xpm";
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr, obj->textura.name, &obj->textura.width, &obj->textura.height);
	obj->textura.data = mlx_get_data_addr(obj->textura.image, &obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	//obj->textura.tab = color_tab(obj->textura.data, obj->textura.width,obj->textura.height );
	return (1);
}

int		load_texture_earth(t_rtv *p,t_object *obj)
{
	obj->textura.name = "xpm/earth.xpm";
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr, obj->textura.name, &obj->textura.width, &obj->textura.height);
	obj->textura.data = mlx_get_data_addr(obj->textura.image, &obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	//obj->textura.tab = color_tab(obj->textura.data, obj->textura.width,obj->textura.height );
	return (1);
}

int		load_texture_grass(t_rtv *p,t_object *obj)
{
	obj->textura.name = "xpm/Grass.xpm";
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr, obj->textura.name, &obj->textura.width, &obj->textura.height);
	obj->textura.data = mlx_get_data_addr(obj->textura.image, &obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	//obj->textura.tab = color_tab(obj->textura.data, obj->textura.width,obj->textura.height );
	return (1);
}

int		load_texture_wood(t_rtv *p,t_object *obj)
{
	obj->textura.name = "xpm/wood.xpm";
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr, obj->textura.name, &obj->textura.width, &obj->textura.height);
	obj->textura.data = mlx_get_data_addr(obj->textura.image, &obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	//obj->textura.tab = color_tab(obj->textura.data, obj->textura.width,obj->textura.height );
	return (1);
}
///////////////////////////////////////////////////

t_vector	vec_normalize(t_vector v)
{
	t_vector	norm;
	float	len;

	len = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}

void	get_tex_coord_sphere(t_object *object, int *column, int *row, t_cross *intersect)
{
	float theta;
	float u;
	float v;
	t_vector npoint;
	t_vector tpoint;

	tpoint = ft_sub_vectors(&object->pos, &intersect->vec3);
	npoint = ft_multkv(1 / ft_lengthv(tpoint), tpoint) ;


	theta = atan2(npoint.x, npoint.z);
	u = 0.5 + atan2(npoint.z, npoint.x) / M_PI * 0.5; //1 - (theta / (2 * M_PI) + 0.5);
	v = 0.5 - asin(npoint.y) / M_PI;

	*column = (int)(object->textura.width * u);
	*row = (int)(object->textura.height * v);
}


void	get_tex_coord_plane(t_object *object, int *column, int *row, t_cross *intersect)
{
	float u;
	float v;
	t_vector r;

	r = ft_sub_vectors(&object->pos, &intersect->vec3);
	//vector_matrix_multiply(shape->rotation, &r);
	u = r.x * 100; // 2.0;
	v = r.z * 100;// 2.0;
	 
	if (u < 0.0f)
		u *= -1.0f;
	if (v < 0.0f)
		v *= -1.0f;
//printf("u: %f, v: %f\n", u, v);
	*column = (int)u;//(object->textura.width * u);
	*row = (int)v;//(object->textura.height * v);
}


/*
t_vector	ft_vec3(float x, float y, float z)
{
	t_vector res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

float	ft_vec3_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
//ft_plane_uv(o, o->e.plane.normal, pos, &uv);
void	get_tex_coord(t_object *object, int *column, int *row, t_cross *intersect)
{

	float u;
	float v;
	t_vector tpoint;
	t_vector npoint;

	tpoint = ft_vec3(object->axis.y , object->axis.z, -object->axis.x);
	npoint = ft_sub_vectors(&object->pos, &intersect->vec3);

	u = ft_vec3_dot(intersect->vec3, tpoint) * 1.0; 
	v = ft_vec3_dot(intersect->vec3, npoint) * 1.0;
	if (u < 0.0f)
		u *= -1.0f;
	if (v < 0.0f)
		v *= -1.0f;
	*column = (int) u;
	*row = (int) v;
}
*/
/*
void	get_tex_coord(t_object *object, int *column, int *row, t_cross *intersect)
{
	//float theta;
	float u;
	float v;
	t_vector tpoint;
	//t_vector npoint;
	t_vector	axis[2];
	axis[0] = (t_vector){1, 0, 0};
	ft_rotate_vector(&object->angle_n, &axis[0]);
	axis[1] = (t_vector){0, 0, 1};
	ft_rotate_vector(&object->angle_n, &axis[1]);

	tpoint = ft_sub_vectors(&intersect->vec3, &object->pos);
	ft_unit_vector(&tpoint);
	float k_width = (float)object->textura.width / object->min;
    float k_height = (float)object->textura.height / object->max;
	float u1 = ft_vector_projection_on_ray(&tpoint, &axis[0]);
	float v1 = ft_vector_projection_on_ray(&tpoint, &axis[1]);
	u = (u1 - object->min /  2)/object->min;
	v = (v1 - object->max / 2);
	//u = 0.5 + atan2(npoint.z, npoint.x) / M_PI * 0.5; //1 - (theta / (2 * M_PI) + 0.5);
	//v = 0.5 - asin(npoint.y) / M_PI;
	//printf("u: %f, v: %f\n", u, v); 
	if (u < 0.0f)
		u *= -1.0f;
	if (v < 0.0f)
		v *= -1.0f;
	//printf("returning offset %d\n", (int)(u) + (int)(v) * object->textura.width);
	*column = (int)(object->textura.width * k_width);//(object->textura.width * k_width);
	*row = (int)(object->textura.height * k_height);//(object->textura.height * k_height);
	//printf("column: %d, row: %d\n", *column, *row);
}*/

double	ft_flabs(float nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

void	get_tex_coord_cone(t_object *object, int *column, int *row, t_cross *intersect)
{

	float u;
	float v;
	t_vector r;

	r = ft_sub_vectors(&object->pos, &intersect->vec3);
	//vector_matrix_multiply(shape->rotation, &r);
	u = r.x * 300; // 2.0;
	v = r.z * 300;// 2.0;
	 
	if (u < 0.0f)
		u *= -1.0f;
	if (v < 0.0f)
		v *= -1.0f;
//printf("u: %f, v: %f\n", u, v);
	*column = (int)u;//(object->textura.width * u);
	*row = (int)v;//(object->textura.height * v);
}


t_color	get_color_cone(t_object *object, t_cross *intersect)
{
	int		i;
	int		column;
	int		row;
	t_color	color;


	i = 0;
	column = 0;
	row = 0;
	get_tex_coord_cone(object, &column, &row, intersect);
	i = row * object->textura.size_line + object->textura.bpp / 8 * column;
	//printf("%d\n", i);
	color.blue = (int)(unsigned char)object->textura.data[i];//(int)(unsigned char)object->textura.data[i] / 255;
	color.green = (int)(unsigned char)object->textura.data[i + 1];//(int)(unsigned char)object->textura.data[i + 1] / 255;
	color.red = (int)(unsigned char)object->textura.data[i + 2];//(int)(unsigned char)object->textura.data[i + 2] / 255;

	return (color);
}


t_color	get_color_plane(t_object *object, t_cross *intersect)
{
	int		i;
	int		column;
	int		row;
	t_color	color;


	i = 0;
	column = 0;
	row = 0;
	get_tex_coord_plane(object, &column, &row, intersect);
	i = row * object->textura.size_line + object->textura.bpp / 8 * column;
	//printf("%d\n", i);
	color.blue = (int)(unsigned char)object->textura.data[i];//(int)(unsigned char)object->textura.data[i] / 255;
	color.green = (int)(unsigned char)object->textura.data[i + 1];//(int)(unsigned char)object->textura.data[i + 1] / 255;
	color.red = (int)(unsigned char)object->textura.data[i + 2];//(int)(unsigned char)object->textura.data[i + 2] / 255;

	return (color);
}

t_color	get_color_sphere(t_object *object, t_cross *intersect)
{
	int		i;
	int		column;
	int		row;
	t_color	color;


	i = 0;
	column = 0;
	row = 0;
	get_tex_coord_sphere(object, &column, &row, intersect);
	i = row * object->textura.size_line + object->textura.bpp / 8 * column;
	//printf("%d\n", i);
	color.blue = (int)(unsigned char)object->textura.data[i];//(int)(unsigned char)object->textura.data[i] / 255;
	color.green = (int)(unsigned char)object->textura.data[i + 1];//(int)(unsigned char)object->textura.data[i + 1] / 255;
	color.red = (int)(unsigned char)object->textura.data[i + 2];//(int)(unsigned char)object->textura.data[i + 2] / 255;

	return (color);
}
/////////////////////////////

void	get_tex_coord_cylindr(t_object *object, int *column, int *row, t_cross *intersect)
{
	float theta;
	float u;
	float v;
	t_vector npoint;
	t_vector tpoint;

	tpoint = ft_sub_vectors(&object->pos, &intersect->vec3);
	npoint = ft_multkv(1 / ft_lengthv(tpoint), tpoint) ;


	theta = atan2(npoint.x, npoint.z);
	u = 0.5 + atan2(npoint.z, npoint.x) / M_PI * 0.5; //1 - (theta / (2 * M_PI) + 0.5);
	v = 0.5 - asin(npoint.y) / M_PI;

	*column = (int)(object->textura.width * u);
	*row = (int)(object->textura.height * v);
}


t_color	get_color_cylindr(t_object *object, t_cross *intersect)
{
	int		i;
	int		column;
	int		row;
	t_color	color;


	i = 0;
	column = 0;
	row = 0;
	get_tex_coord_cylindr(object, &column, &row, intersect);
	i = row * object->textura.size_line + object->textura.bpp / 8 * column;
	//printf("%d\n", i);
	color.blue = (int)(unsigned char)object->textura.data[i];//(int)(unsigned char)object->textura.data[i] / 255;
	color.green = (int)(unsigned char)object->textura.data[i + 1];//(int)(unsigned char)object->textura.data[i + 1] / 255;
	color.red = (int)(unsigned char)object->textura.data[i + 2];//(int)(unsigned char)object->textura.data[i + 2] / 255;

	return (color);
}

t_color	get_color(t_object *object, t_cross *intersect)
{
t_color color;
if (object->type == e_sphere)
	color = get_color_sphere(object, intersect);
if (object->type == e_plane)
    color = get_color_plane(object, intersect);
if (object->type == e_cone)
	color = get_color_cone(object, intersect);
if (object->type == e_cylindr) 
	color = get_color_cylindr(object, intersect);
return (color);
}

/////////////////////////////
t_color int_to_rgb(int p)
{
	t_color c;

	c.red = (p >> 16) & 0xFF;
	c.green = (p >> 8) & 0xFF;
	c.blue = (p) & 0xFF;
	return(c);
}

void	anaglyph(t_rtv *scene, int p1, int p2, int p)
{
	t_color c1;
	t_color c2;
	t_color c;

	c1 = int_to_rgb(scene->draw[p1]);
	c2 = int_to_rgb(scene->draw[p2]);
	c = int_to_rgb(scene->draw[p]);

	c.red = c1.red * 0.299 + c1.green * 0.587 + c1.blue * 0.114;
	c.green = 0;
	c.blue = c2.red * 0.299 + c2.green * 0.587 + c2.blue * 0.114;
	scene->filtered_data[p] = ((c.red << 16) | (c.green << 8) | c.blue);
}



void	mb(t_rtv *scene, int p1, int p2, int p)
{

	t_color c1;
	t_color c2;
	t_color c;

	c1 = int_to_rgb(scene->draw[p1]);
	c2 = int_to_rgb(scene->draw[p2]);
	c = int_to_rgb(scene->draw[p]);
	c.red = (c1.red/3 + c.red/3 + c2.red/3);
	c.green = (c1.green/3 + c.green/3 + c2.green/3);
	c.blue = (c1.blue/3 + c.blue/3 + c2.blue/3);
	scene->filtered_data[p] = ((c.red << 16) | (c.green << 8) | c.blue);
}

void motion_bluer(t_rtv *scene)
{
	int		i;
	int		j;
	int		p;
	int		p1;
	int		p2;

	i = 0;
	j = 0;
	while (j < scene->height)
	{
		while (i < scene->width)
		{
			p = scene->width * j + i;
			p1 = scene->width * j + i - 3;
			p2 = scene->width * j + i + 3;
			if ((i - 3) < 0)
				p1 = p;
			if ((i + 3) > scene->width - 1)
				p2 = p;
			 mb(scene, p1, p2, p);
			i++;
		}
		i = 0;
		j++;
	}
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->filtered_img, 0, 0);
}

void color_to_anaglyph(t_rtv *scene)
{
	int		i;
	int		j;
	int		p;
	int		p1;
	int		p2;

	i = 0;
	j = 0;
	while (j < scene->height)
	{
		while (i < scene->width)
		{
			p = scene->width * j + i;
			p1 = scene->width * j + i - 3;
			p2 = scene->width * j + i + 3;
			if ((i - 3) < 0)
				p1 = p;
			if ((i + 3) > scene->width - 1)
				p2 = p;
			anaglyph(scene, p1, p2, p);
			i++;
		}
		i = 0;
		j++;
	}
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->filtered_img, 0, 0);
}


/*

int		ft_isspace(int c)
{
	if (c == '\t' || c == ' ' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void		free_split(char **split)
{
	int i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}


void		free_size_obj(int *size, t_object *object)
{
	free(size);
	free(object);
}

void		free_color_tab(int **tab, int y)
{
	while (y)
	{
		free(tab[y - 1]);
		y--;
	}
	free(tab);
}


void	replace_char(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str) && !ft_isdigit(*str))
			*str = ' ';
		str++;
	}
}

int		*get_wh(char *str, int *wh)
{
	char **split;

	replace_char(str);
	if (!(split = ft_strsplit(str, ' ')))
	{
		free(wh);
		free(str);
		return (NULL);
	}
	wh[0] = ft_atoi(split[0]);
	wh[1] = ft_atoi(split[1]);
	free_split(split);
	free(str);
	return (wh);
}

int		*get_xpm_size(char *file, t_object *obj)
{
	int		fd;
	int		line;
	int		*wh;
	char	*str;

	line = 0;
	fd = open(file, O_RDONLY);
	if (!(wh = (int *)malloc(sizeof(int) * 2)) || fd < 0)
	{
		free(obj);
		ft_putstr_fd("Texture file size could not be loaded !\n", 2);
		return (NULL);
	}
	while (get_next_line(fd, &str) == 1 && line <= 4)
	{
		line++;
		if (line == 4)
			return (get_wh(str, wh));
		free(str);
	}
	free(str);
	return (NULL);
}

int		**color_tab(int *imgstr, int *size)
{
	int		**color_tab;
	int		x;
	int		y;
	int		i;

	y = -1;
	i = 0;
	if (!(color_tab = (int **)malloc(sizeof(int*) * size[1] * 2)) || !imgstr)
		return (NULL);
	while (++y < size[1])
	{
		if (!(color_tab[y] = (int *)malloc(sizeof(int) * size[0] * 2)))
		{
			free_color_tab(color_tab, y);
			return (NULL);
		}
		x = -1;
		while (++x < size[0])
		{
			color_tab[y][x] = imgstr[i];
			i++;
		}
	}
	return (color_tab);
}
*/
