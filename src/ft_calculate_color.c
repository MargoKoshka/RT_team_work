#include "rtv1.h"

double		illumination(int specular,
					t_vector *ray, t_vector *reflect, t_vector *norm)
{
	double	shade;
	double	shine;

	shine = 0.0;
	shade = ft_vector_scalar(norm, ray);
	if (shade < 0)
		shade = 0;
	if (shade >= 0 && specular != 0)
		shine = ft_vector_scalar(ray, reflect);
	if (shine > 0)
		shade = shade + powf(shine, specular);
	return (shade);
}

double		is_point_shadow(t_object **object, t_vector *intersect, t_vector *ray, double *k_light)
{
	t_object	tmp_object;
	t_vector	new_start;
	double		len_light;
	t_cross		obj;
	int			n;

	len_light = ft_vector_modul(ray);
	ft_unit_vector(ray);
	new_start = ft_multiply_vector_num(intersect, 0.99);
	// new_start = new_start_vector(intersect, ray, 0.001);
	*k_light = 1.0;
	n = 0;
	while (NULL != object[n])
	{
		tmp_object = *object[n];
		object_data(&tmp_object, &new_start);
		obj = ft_raytrace_objects(&tmp_object, ray);
		if ((0.001 < obj.len && obj.len < len_light) && obj.id == INTERSECT)
		{
			*k_light *= tmp_object.refraction;
			if (tmp_object.refraction == 0)
				return (*k_light);
		}
		n += 1;
	}
	return (*k_light);
}

t_vector	ft_vector_light_cross(t_light *source, t_vector *intersect)
{
	t_vector light_cross;

	if (source->tip == e_point)
		light_cross = ft_sub_vectors(&source->pos, intersect);
	if (source->tip == e_direct)
		light_cross = source->pos;
	return (light_cross);
}

double		ft_calculate_lighting(t_rtv *p, t_cross *cross, t_vector *norm)
{
	t_vector	light_cross;
	t_vector	reflect;
	t_light		*source;
	double		k_light;
	double		shade;

	shade = 0.0;
	source = p->light;
	while (source != NULL)
	{
		if (source->tip == e_ambient)
			shade += source->intensity;
		if (source->tip == e_point || source->tip == e_direct)
		{
			light_cross = ft_vector_light_cross(source, &cross->vec3);
			reflect = ft_reflection_ray(&cross->vec3, norm); // Model Fonga
			k_light = is_point_shadow(p->object, &cross->vec3, &light_cross, &k_light);
			shade += source->intensity * k_light *
	illumination(p->object[cross->id]->specular, &light_cross, &reflect, norm);
		}
		source = source->next;
	}
	return (shade);
}
////////////////////////////////////////////////////////////////////////////////

int			color_limits(int col)
{
	if (col < 0)
		return (0);
	if (col > 255)
		return (255);
	else
		return (col);
}

t_vector	hextorgb(int hex)
{
	t_vector rgb;

	rgb.x = (int)((hex / (0x100 * 0x100)) % 0x100);
	rgb.y = (int)((hex / 0x100) % 0x100);
	rgb.z = (int)(hex % 0x100);
	return (rgb);
}

int		sepia(int color)
{
	t_vector rgb;
	t_vector sepiargb;

	rgb = hextorgb(color);
	sepiargb.x = ((double)(rgb.x * 393) + (rgb.y * 769) + (rgb.z * 189)) / 1000;
	sepiargb.y = ((double)(rgb.x * 349) + (rgb.y * 686) + (rgb.z * 168)) / 1000;
	sepiargb.z = ((double)(rgb.x * 272) + (rgb.y * 534) + (rgb.z * 131)) / 1000;
	return (color_limits(sepiargb.x) * 256 * 256 +
	color_limits(sepiargb.y) * 256 + color_limits(sepiargb.z));
}

int			ft_local_color(t_rtv *p, t_cross *intersect, t_vector *norm)
{
	double		shade;
	t_color c; 
	int last_color = 0;
	if	(p->filter == 'X')
		recalculate_values(&intersect->vec3.x, &intersect->vec3.y);
	shade = ft_calculate_lighting(p, intersect, norm);
	if ( p->object[intersect->id]->texture == CHESS)
	{
		c = ft_get_texture_color(p->object[intersect->id], intersect->vec3);
		last_color = color(&c, shade);
	}
	else if (p->object[intersect->id]->texture == EARTH || p->object[intersect->id]->texture == BLUR || p->object[intersect->id]->texture == WOOD || p->object[intersect->id]->texture == GRASS)
	{
		c = get_color(p->object[intersect->id], intersect);
		last_color = color(&c, shade);
	}
	else if (p->object[intersect->id]->texture == NO_TEXTURE)
	{
		//c = get_color(p->object[intersect->id], intersect);
		last_color = color(&p->object[intersect->id]->color,shade);
	}
	else if (p->object[intersect->id]->texture == PERLIN)
	{
		c = makenoise_perlin(intersect, p->object[intersect->id]->perlin_tab, &p->object[intersect->id]->color);
		last_color = color(&c, shade);
	}
	else if (p->object[intersect->id]->texture == MARBLE)
	{
		c = makenoise_marble(intersect, p->object[intersect->id]->perlin_tab, &p->object[intersect->id]->color);
		last_color = color(&c, shade);
	}
		//last_color = color(&p->object[intersect->id]->color, shade);
	
	if	(p->filter == 'O')
		last_color =  sepia(last_color);
	/*if	(p->filter == 'X')
	{
		c = wave(intersect->vec3.x, intersect->vec3.y, p->object[intersect->id]->color);
		last_color = color(&c, shade);
	}*/
	
	return(last_color);
}

void			recalculate_values(double *x, double *y)
{
	*x = *x / 960 + sin(6.2831853071);
	*y = *y / 960 + cos(6.2831853071);
}
/*
t_color			wave(double x, double y, t_color color)
{
	recalculate_values(&x, &y);
	x *= (double)960 / 960;
	x += sin(y * 3.) / 10.;
	y += sin(x * 4.) / 5.;
	if (fmod(y + y, .2) <= 0.1)
	{
		color.blue= (int)(color.blue);
		color.green = (int) (color.green * 0.75);
		color.red = (int)color.red  ;
	}
	else
	{
		color.blue= (int)(color.blue * 0.87);
		color.green = (int) (color.green);
		color.red = (int)color.red  ;
	}
	
	return (color);
}*/



/*
t_channel			wave(t_vec p)
{
	float		u;
	double		v;
	t_channel	color;

	u = floor(sin(p.x)) + floor(sin(p.y)) + floor(sin(p.z));
	u = modf(u * 0.5, &v);
	u = u * 3;
	color = (t_channel){((int)u >> 16) & 0xFF, ((int)u >> 16) & 0xFF,
						(((int)u >> 16) & 0xFF)};
	return (color);
}
*/


t_color			set_color_cartoon(t_color color, double light)
{
	t_color c;
	if (light < 0.3)
		light = 0.3;
	else if (light < 0.7)
		light = 0.7;
	else
		light = 1.0;
	c.red = color.red * light;
	c.green = color.green * light;
	c.blue = color.blue * light;
	return(c);
}



	//else if (p->object[intersect->id]->texture == NO_TEXTURE )
	//	return (color(&p->object[intersect->id]->color, shade));
	/*if ( p->object[intersect->id]->texture == CHESS)
	{
		c = get_color(p->object[intersect->id], intersect);
		return (color(&c, shade));
	}*/
	//else
	//	c = color(&p->object[intersect->id]->color, shade);

	
	/*{
		p->object[intersect->id]->color = get_color(p->object[intersect->id], intersect);
		return(get_color(p->object[intersect->id], intersect));// color(&p->object[intersect->id]->color, shade)); // тут достаю цвет пикселя
	}*/
