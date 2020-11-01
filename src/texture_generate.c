#include "rtv1.h"
#include <stdio.h>

t_vector	ft_multkv(double k, t_vector v)
{
	t_vector	m;

	m.x = k * v.x;
	m.y = k * v.y;
	m.z = k * v.z;
	return (m);
}

double	ft_dotprod(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	ft_lengthv(t_vector v)
{
	return (sqrt(ft_dotprod(v, v)));
}

int ft_gen_chess(int countu, int countv, double u, double v)
{
	double i;
	double j;
	i = 0;
	j = 0;
	i = (int)(u/(1/(double)countu)) ;
	j = (int)(v / (1/(double)countv));
	if ((int)(i+j) % 2 == 0)
		return(1);
	else 
		return (0);
}
/*
int ft_gen_column(int countu, double u)
{
	double i;

	i = 0;
	i = (int)(u/(1/(double)countu)) ;
	if ((int)(i) % 2 == 0)
		return(1);
	else 
		return (0);
}
t_color ft_map_texture_sphere(t_object *object, t_vector point)
{
	double theta;
	t_color color;
	double u;
	double v;
	t_vector npoint;
	t_vector tpoint;

	tpoint = ft_sub_vectors(&object->pos, &point);
	npoint = ft_multkv(1 / ft_lengthv(tpoint), tpoint) ;


theta = atan2(npoint.x, npoint.z);
u = 1 - (theta / (2 * M_PI) + 0.5);
v = 0.5 - asin(npoint.y) / M_PI;

if (ft_gen_column(18,u) == 0)
{
color.red = 0;
color.green = 0;
color.blue = 0;
}
else
{
color = object->color;
}
return(color);
}
*/

t_color ft_map_texture_sphere(t_object *object, t_vector point)
{
	double theta;
	t_color color;
	double u;
	double v;
	t_vector npoint;
	t_vector tpoint;

	tpoint = ft_sub_vectors(&object->pos, &point);
	npoint = ft_multkv(1 / ft_lengthv(tpoint), tpoint) ;


theta = atan2(npoint.x, npoint.z);
u = 1 - (theta / (2 * M_PI) + 0.5);
v = 0.5 - asin(npoint.y) / M_PI;

if (ft_gen_chess(16,8,u,v) == 0)
{
color.red = 0;
color.green = 0;
color.blue = 0;
}
else
{
color = object->color;
}
return(color);
}

/*
int ft_gen_lines(int countv, double v)
{
	double j;
	j = 0;
	j = (int)(v / (1/(double)countv));
	if ((int)(j) % 2 == 0)
		return(1);
	else 
		return (0);
}

t_color ft_map_texture_sphere(t_object *object, t_vector point)
{
	double theta;
	t_color color;
	double u;
	double v;
	t_vector npoint;
	t_vector tpoint;

	tpoint = ft_sub_vectors(&object->pos, &point);
	npoint = ft_multkv(1 / ft_lengthv(tpoint), tpoint) ;


	theta = atan2(npoint.x, npoint.z);
	u = 1 - (theta / (2 * M_PI) + 0.5);
	v = 0.5 - asin(npoint.y) / M_PI;

	if (ft_gen_lines(8,v) == 0)
	{
	color.red = 0;
	color.green = 0;
	color.blue = 0;
	}
	else	
	{
		color = object->color;
	}
	return(color);
}*/


t_color ft_map_texture_plane(t_object *object, t_vector point)
{
t_color color;
double u;
double v;

u = point.x - (int) point.x;
v = point.z - (int) point.z;

if (ft_gen_chess(6,6,u,v) == 0)
{
color.red = 0;
color.green = 0;
color.blue = 0;
}
else
{
color = object->color;
}
return(color);
}

t_color ft_map_texture_cylindr(t_object *object, t_vector point)
{
double theta;
t_color color;
double u;
double v;
t_vector npoint;
t_vector tpoint;

tpoint = ft_sub_vectors(&object->pos, &point);
npoint = ft_multkv(1 / ft_lengthv(tpoint), tpoint) ;


theta = atan2(npoint.x, npoint.z);
u = 1 - (theta / (2 * M_PI) + 0.5);
//v = 0.5 - asin(npoint.y) / M_PI;
v = point.y - (int) point.y;

if (ft_gen_chess(16,8,u,v) == 0)
	{
		color.red = 0;
		color.green = 0;
		color.blue = 0;
	}
else
	{
		color = object->color;
	}
return(color);
}

t_color ft_get_texture_color(t_object *object, t_vector point)
{
t_color color;
//if ((object->type == 1)|| (object->type == 4))
color = ft_map_texture_sphere(object, point);
////if (object->type == 2)
//color = ft_map_texture_plane(object, point);
//if (object->type == 3) 
//color = ft_map_texture_cylindr(object, point);
return (color);
}
