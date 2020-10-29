#include "rtv1.h"

int			color(t_color *color, float percent)
{
	float	red;
	float	green;
	float	blue;

	if (percent > 1)
		percent = 1.0;
	red = (float)color->red * percent;
	green = (float)color->green * percent;
	blue = (float)color->blue * percent;
	return (((int)red << 16) | ((int)green << 8) | (int)blue);
}

int			get_light(int color1, int color2, float coefficient)
{
	if (coefficient > 1.0)
		coefficient = 1.0;
	return ((int)(color1 * (1.0 - coefficient) + color2 * coefficient));
}

int			result_color(int color1, int color2, float coefficient)
{
	float	red;
	float	green;
	float	blue;

	if (color1 == color2 || color2 < 0 || coefficient == 0)
		return (color1);
	red = get_light((color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF, coefficient);
	green = get_light((color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF, coefficient);
	blue = get_light(color1 & 0xFF, color2 & 0xFF, coefficient);
	return (((int)red << 16) | ((int)green << 8) | (int)blue);
}

int			calculate_result_color(float color[][2], int depth, int max_depth)
{
	if (depth == max_depth)
		depth -= 1;
	while (depth > 0)
	{
		color[depth - 1][0] = result_color(color[depth - 1][0],
								color[depth][0], color[depth - 1][1]);
		depth -= 1;
	}
	return (int)color[0][0];
}

t_vector	ft_reflection_ray(t_vector *ray, t_vector *norm)
{
	t_vector	reflection_ray;

	reflection_ray = (t_vector){ray->x, ray->y, ray->z};
	// ft_unit_vector(&reflection_ray);
	reflection_ray =
		ft_multiply_vector_num(norm, 2 * ft_vector_scalar(norm, ray));
	reflection_ray = ft_sub_vectors(ray, &reflection_ray);
	ft_unit_vector(&reflection_ray);
	return (reflection_ray);
}

// int		add_colors(int color1, int color2)
// {
// 	int red;
// 	int green;
// 	int blue;

// 	red = ((color1 >> 16) & 0xFF) + ((color2 >> 16) & 0xFF);
// 	green = ((color1 >> 8) & 0xFF) + ((color2 >> 8) & 0xFF);
// 	blue = (color1 & 0xFF) + (color2 & 0xFF);
// 	return (((int)red << 16) | ((int)green << 8) | (int)blue);
// }

// int		avg_color(int color1, int num)
// {
// 	int red;
// 	int green;
// 	int blue;

// 	red = ((color1 >> 16) & 0xFF) / (float)num;
// 	green = ((color1 >> 8) & 0xFF) / (float)num;
// 	blue = (color1 & 0xFF) / (float)num;
// 	return (((int)red << 16) | ((int)green << 8) | (int)blue);
// }

t_color		color_2(t_color *color, float percent)
{
	t_color	new_color;

	if (percent > 1)
		percent = 1.0;
	new_color.red = (int)(color->red * percent);
	new_color.green = (int)(color->green * percent);
	new_color.blue = (int)(color->blue * percent);
	return (new_color);
}

t_color		add_color_2(t_color *color1, t_color *color2)
{
	t_color	new_color;

	new_color.red = color1->red + color2->red;
	new_color.green = color1->green + color2->green;
	new_color.blue = color1->blue + color2->blue;
	return (new_color);
}