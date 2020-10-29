




t_vector			rt_getcolor(t_timage img, int x, int y)
{
	int		color;
	int		c;

	c = (y * img.width + x) * 4;
	color = img.buffer_ptr[c];
	if (color == -120 && img.buffer_ptr[c + 1] == 0
		&& img.buffer_ptr[c + 2] == -104)
		return ((t_vector) {1, 1, 1});
	color += img.buffer_ptr[c + 1] * 256;
	color += img.buffer_ptr[c + 2] * 256 * 256;
	return (rt_attribute_color(color));
}

t_vector			rt_map_sphere(t_vector normal, t_vector intercolor,
		t_inter *inter, t_env *env)
{
	float		u;
	float		v;
	int			i;

	i = 3;
	while (--i + 1)
		normal = ft_vrotate(normal, env->form[inter->id].mat[i]);
	u = 0.5 + atan2(normal.z, normal.x) / M_PI * 0.5;
	v = 0.5 - asin(normal.y) / M_PI;
	u = (int)(u * env->form[inter->id].timage.width
		+ env->form[inter->id].texture.offsetx)
		% env->form[inter->id].timage.width;
	v = (int)(v * env->form[inter->id].timage.height
		+ env->form[inter->id].texture.offsety)
		% env->form[inter->id].timage.height;
	intercolor = rt_getcolor(env->form[inter->id].timage, (int)u, (int)v);
	return (intercolor);
}