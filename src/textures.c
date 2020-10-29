#include "rtv1.h"
#include <stdio.h>

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

int		load_texture(t_rtv *p,t_object *obj)
{
	//t_mapping	*m;
	
	//void	*mlx;
	//void	*image; - obj->textura.image
	//int		*imgstr; - 	obj->textura.data 
	//int		*size = NULL;
	// &size[0] - &obj->textura.width, 
	//&size[1] - &obj->textura.height
	//int		a[3]; &a[0] - &obj->textura.bpp, 
	//&a[1] - &obj->textura.size_line    stride
	//&a[2] - &obj->textura.endian
	
	obj->textura.name = "xpm/earth.xpm";
//	if (!(obj->file_txt.size = get_xpm_size("xpm/earth_height.xpm", obj))) //obj->file_height.size
//		return (0);
	//size = get_xpm_size("xpm/earth_height.xpm", obj);
//	size = obj->file_txt.size;
	//mlx = mlx_init();
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr, obj->textura.name, &obj->textura.width, &obj->textura.height);
	//obj->textura.data = (int *)mlx_get_data_addr(obj->textura.image, &obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	obj->textura.data = mlx_get_data_addr(obj->textura.image, &obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
		//if (!(obj->file_txt.tab = color_tab(obj->textura.data, size)))
	//if (!(obj->texture_tab = create_color_tab(obj->textura.data, obj->textura.width, obj->textura.height)))
	//	return (0);
	//k = obj->file_txt.tab;
	//printf("Color%d \n",k[3][4]);
	//p->obj->color->red
	//p->obj->color->green
	//p->obj->color->blue
	return (1);
}
/*
t_color	get_pixel_vector(t_textura *textura, int x, int y)
{
	size_t	i;
	t_color dest;
	
		i = ((x * textura->bpp) / 8) + (y * textura->size_line);
		dest.blue = (unsigned char)(textura->data[i + 2]) / 255.0;
		dest.green = (unsigned char)(textura->data[i + 1]) / 255.0;
		dest.red = (unsigned char)(textura->data[i]) / 255.0;
	
	return (dest);
}

t_color		color_from_texture(t_vector *sample, t_textura *textura)
{
	int		x;
	int		y;
	t_color dest;

	x = textura->width - sample->x;
	y = sample->y;
	dest = get_pixel_vector(textura, x, y);
	return(dest);
}

void		vec(double a, double b, double c, t_vector *dest)
{
	dest->x = a;
	dest->y = b;
	dest->z = c;
}

t_vector		texture_coord(double u, double v, t_textura *texture, int index)
{
	int		x;
	int		y;
	int		environment;
	t_vector	res;

	environment = (index >= 0) ? 1 : 0;
	if (environment)
		texture->scale = 1.0;
	x = (double)(texture->width - 1.0) * u * texture->scale;
	y = (double)(texture->height - 1.0) * v * texture->scale;
	x = x % (texture->width - 1);
	y = y % (texture->height - 1);
	if (environment)
		vec((double)(texture->width - x), \
			(double)(texture->height - y), 0.0, &res);
	else
		vec((double)(x), (double)(y), 0.0, &res);
	return (res);
}

t_vector			ft_vrotate(t_vector v, double mat[3][3])
{
	double			tmpx;
	double			tmpy;
	t_vector		result;

	tmpx = v.x;
	tmpy = v.y;
	result.x = mat[0][0] * tmpx + mat[0][1] * tmpy + mat[0][2] * v.z;
	result.y = mat[1][0] * tmpx + mat[1][1] * tmpy + mat[1][2] * v.z;
	result.z = mat[2][0] * tmpx + mat[2][1] * tmpy + mat[2][2] * v.z;
	return (result);
}

t_color		get_color(t_object *object, t_vector *normal)
{
	double	u;
	double	v;
	t_vector	sample;
	int			i;
	t_color cvet;

	i = 3;
	while (--i + 1)
		normal = ft_vrotate(normal, object->mat[i]);
	u = 0.5 + atan2(normal->z, normal->x) / M_PI * 0.5;
	v = 0.5 - asin(normal->y) / M_PI;
	sample = texture_coord(u, v, &object->textura, -1);
	cvet = color_from_texture(&sample, &object->textura);

	return(cvet);
}



*/








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

void	get_tex_coord(t_object *object, int *column, int *row, t_cross *intersect)
{
	float	u;
	float	v;
	t_vector	n;

	//n = vec_normalize(ft_sub_vectors(&intersect->vec3, &object->pos));
	//ft_unit_vector(&n);
	n = ft_sub_vectors(&intersect->vec3, &object->pos);
	ft_unit_vector(&n);
	u = 0.5 + atan2(n.z, n.x) / (2 * M_PI);
	v = 0.5 - asin(n.y) / M_PI;
	*column = (int)(object->textura.width * u);
	*row = (int)(object->textura.height * v);
}

int	get_color(t_object *object, t_cross *intersect)
{
	int		i;
	int		column;
	int		row;
	t_color	color;

	i = 0;
	column = 0;
	row = 0;
	get_tex_coord(object, &column, &row, intersect);
	i = row * object->textura.size_line + object->textura.bpp / 8 * column;
	color.blue = (float)(unsigned char)object->textura.data[i] / 255;
	color.green = (float)(unsigned char)object->textura.data[i + 1] / 255;
	color.red = (float)(unsigned char)object->textura.data[i + 2] / 255;
	return (((int)color.red << 16) | ((int)color.green << 8) | (int)color.blue);
}
/////////////////////////////

/*


t_color		rt_attribute_color(int color)
{
	t_color	vcolor;

	vcolor.x = (double)(color >> 16 & 0xFF) / 255;
	vcolor.y = (double)(color >> 8 & 0xFF) / 255;
	vcolor.z = (double)(color & 0xFF) / 255;
	return (vcolor);
}

t_vector			rt_getcolor(t_textura img, int x, int y)
{
	int		color;
	int		c;

	c = (y * img.width + x) * 4;
	color = img.data[c];
	if (color == -120 && img.data[c + 1] == 0
		&& img.data[c + 2] == -104)
		return ((t_vector) {1, 1, 1});
	color += img.data[c + 1] * 256;
	color += img.data[c + 2] * 256 * 256;
	return (rt_attribute_color(color));
}

t_vector			rt_map_sphere(t_vector normal, t_color *color,
		t_cross *intersect, t_rtv *env)
{
	float		u;
	float		v;
	int			i;

	i = 3;
	while (--i + 1)
		normal = ft_vrotate(normal, env->form[intersect->id].mat[i]);
	u = 0.5 + atan2(normal.z, normal.x) / M_PI * 0.5;
	v = 0.5 - asin(normal.y) / M_PI;
	u = (int)(u * env->object[intersect->id].textura.width)
		% env->object[intersect->id].textura.width;
	v = (int)(v * env->object[inter->id].textura.height)
		% env->object[intersect->id].textura.height;
	color = rt_getcolor(env->object[intersect->id].textura, (int)u, (int)v);
	return (color);
}

t_vector			rt_tmap(t_vector normal, t_color *color, t_rtv *p, t_cross *intersect)
{
	color = rt_map_sphere(normal, color, intersect, p);
	return (color);
}

*/
/*
int			ft_sph_txt_map(t_object *obj, t_vec3 *normal, t_vec3 *point)
{
	float u = ft_clamp(0.5f + (float)atan2f(normal->z, normal->x) / (float)(2.0f * CL_M_PI), 0.0f, 1.0f);
	float v = ft_clamp(0.5f - (float)asinf(normal->y) / (float)(CL_M_PI), 0.0f, 1.0f);
	obj->uv->x = u;
	obj->uv->y = v;
	int tx = (float)u * (float)obj->txt->w;
	int ty = (float)v * (float)obj->txt->h;
	int color = obj->textura.data[ty * obj->txt->w + tx];

	return (color);
}
*/


/*  solaldunckel   raytrace.c
t_color	ray_intersect(t_mini_rt *rt)
{

rt->sky ? rt->color = get_sky_coord(rt) : rt->color;

if (rt->obj)
	{
		rt->p = vec_add(rt->ray.ori, vec_mul(rt->ray.dir, rt->k));
		rt->color = get_color(rt);
		rt->obj->ref ? reflect(rt) : 0;
		rt->color = apply_lights(rt);
	}
	return (rt->color);
}

t_color		get_sky_color(t_texture sky, float x, float y, float max)
{
	int		i;
	int		column;
	int		row;
	t_color	color;

	max = fabs(max);
	column = (int)(sky.width * (0.5 * (x / max + 1)));
	row = (int)(sky.height * (0.5 * (y / max + 1)));
	i = row * sky.size_line + sky.bpp / 8 * column;
	color.b = (float)(unsigned char)sky.img[i] / 255;
	color.g = (float)(unsigned char)sky.img[i + 1] / 255;
	color.r = (float)(unsigned char)sky.img[i + 2] / 255;
	return (color);
}
void		free_sky(t_mini_rt *rt)
{
	int		i;

	i = 0;
	while (rt->sky[i].img)
	{
		if (rt->sky[i].img)
			mlx_destroy_image(rt->mlx_ptr, rt->sky[i].ptr);
		i++;
	}
	free(rt->sky);
}

t_color		get_sky_coord(t_mini_rt *rt)
{
	t_color	color;
	float	m;

	ft_bzero(&color, sizeof(t_color));
	rt->ray.dir = vec_normalize(rt->ray.dir);
	if (fabs(rt->ray.dir.z) >= fabs(rt->ray.dir.y) && fabs(rt->ray.dir.z)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.z < 0 && (m = rt->ray.dir.z) > -10)
		color = get_sky_color(rt->sky[0], -rt->ray.dir.x, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.z) >= fabs(rt->ray.dir.y) && fabs(rt->ray.dir.z)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.z > 0 && (m = rt->ray.dir.z) > -10)
		color = get_sky_color(rt->sky[1], rt->ray.dir.x, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.x) > fabs(rt->ray.dir.z) && fabs(rt->ray.dir.x)
	> fabs(rt->ray.dir.y) && rt->ray.dir.x < 0 && (m = rt->ray.dir.x) > -10)
		color = get_sky_color(rt->sky[2], rt->ray.dir.z, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.x) > fabs(rt->ray.dir.z) && fabs(rt->ray.dir.x)
	> fabs(rt->ray.dir.y) && rt->ray.dir.x > 0 && (m = rt->ray.dir.x) > -10)
		color = get_sky_color(rt->sky[3], -rt->ray.dir.z, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.y) >= fabs(rt->ray.dir.z) && fabs(rt->ray.dir.y)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.y < 0 && (m = rt->ray.dir.y) > -10)
		color = get_sky_color(rt->sky[4], -rt->ray.dir.x, rt->ray.dir.z, m);
	else if (fabs(rt->ray.dir.y) >= fabs(rt->ray.dir.z) && fabs(rt->ray.dir.y)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.y > 0 && (m = rt->ray.dir.y) > -10)
		color = get_sky_color(rt->sky[5], rt->ray.dir.x, rt->ray.dir.z, m);
	return (color);
}


*/





/*
	obj->textura.name = "xpm/earth.xpm";
	//if (!(obj->textura.size = get_xpm_size("xpm/earth_height.xpm", obj))) //obj->file_height.size
	//	return (0);
	obj->file_height.size = get_xpm_size("xpm/earth_height.xpm", obj); //obj->file_height.size
	//size = get_xpm_size("xpm/earth.xpm");
	//mlx = mlx_init();
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr, obj->textura.name, &obj->textura.width, &obj->textura.height);
	obj->textura.data = (int *)mlx_get_data_addr(obj->textura.image, &obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	if (!(obj->file_height.tab = color_tab(obj->textura.data, obj->file_height.size)))
	//if (!(obj->texture_tab = create_color_tab(obj->textura.data, obj->textura.width, obj->textura.height)))
		return (0);
	return (1);
} */
/*
	obj->textura.name = "xpm/earth.xpm";
	if (!(obj->textura.size = get_xpm_size("xpm/earth_height.xpm", obj))) //obj->file_height.size
		return (0);
	//size = get_xpm_size("xpm/earth.xpm");
	//mlx = mlx_init();
	obj->textura.image = mlx_xpm_file_to_image(p->mlx_ptr, obj->textura.name, &obj->textura.width, &obj->textura.height);
	obj->textura.data = (int *)mlx_get_data_addr(obj->textura.image, &obj->textura.bpp, &obj->textura.size_line, &obj->textura.endian);
	if (!(obj->file_height.tab = color_tab(obj->textura.data, obj->file_height.size)))
	//if (!(obj->texture_tab = create_color_tab(obj->textura.data, obj->textura.width, obj->textura.height)))
		return (0);
	return (1);
}*/

/*

int	texture_getcolor(t_image *texture, t_color *color, \
			 int *pos)
{
  int	i;

  pos[X] = (pos[X] < 0) ? 0 : pos[X];
  pos[Y] = (pos[Y] < 0) ? 0 : pos[Y];
  i = (pos[Y] * texture->sizeline) + (pos[X] * (texture->bpp / 8));
  color->red = (float)(unsigned char)texture->data[i + 2];
  color->green = (float)(unsigned char)texture->data[i + 1];
  color->blue = (float)(unsigned char)texture->data[i];
  return (EXIT_SUCCESS);
}


*/