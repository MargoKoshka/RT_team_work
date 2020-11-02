#include "rtv1.h"

int		*create_perlinmap(void)
{
	int *permutation;
	int i;

	i = 0;
	permutation = (int *)malloc(sizeof(int) * 256);
	if (permutation)
	{
		while (i < 256)
		{
			permutation[i] = rand() % 256;
			i++;
		}
	}
	else
		return(0);
	return (permutation);
}

static double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

static double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

static double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	u = ((h < 8 || h == 12 || h == 13) ? x : y);
	v = ((h < 4 || h == 12 || h == 13) ? y : z);
	return (((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v));
}

static double	compute_noise(t_noise perlin, double x, double y, double z)
{
	return (lerp(perlin.w, lerp(perlin.v, lerp(perlin.u,
		grad(perlin.tab[perlin.aa], x, y, z),
		grad(perlin.tab[perlin.ba], x - 1, y, z)),
		lerp(perlin.u, grad(perlin.tab[perlin.ab], x, y - 1, z),
		grad(perlin.tab[perlin.bb], x - 1, y - 1, z))),
		lerp(perlin.v, lerp(perlin.u,
		grad(perlin.tab[perlin.aa + 1], x, y, z - 1),
		grad(perlin.tab[perlin.ba + 1], x - 1, y, z - 1)),
		lerp(perlin.u, grad(perlin.tab[perlin.ab + 1], x, y - 1, z - 1),
		grad(perlin.tab[perlin.bb + 1], x - 1, y - 1, z - 1)))));
}

double			noise3(double x, double y, double z, int *perlin_tab)
{
	t_noise	perlin;
	int		i;

	i = -1;
	while (++i < 256)
	{
		perlin.tab[i] = perlin_tab[i];
		perlin.tab[256 + i] = perlin_tab[i];
	}
	perlin.cx = (int)floor(x) & 255;
	perlin.cy = (int)floor(y) & 255;
	perlin.cz = (int)floor(z) & 255;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	perlin.u = fade(x);
	perlin.v = fade(y);
	perlin.w = fade(z);
	perlin.a = perlin.tab[perlin.cx] + perlin.cy;
	perlin.aa = perlin.tab[perlin.a] + perlin.cz;
	perlin.ab = perlin.tab[perlin.a + 1] + perlin.cz;
	perlin.b = perlin.tab[perlin.cx + 1] + perlin.cy;
	perlin.ba = perlin.tab[perlin.b] + perlin.cz;
	perlin.bb = perlin.tab[perlin.b + 1] + perlin.cz;
	return (compute_noise(perlin, x, y, z));
}

t_color		makenoise_perlin(t_cross *intersect, int *perlin_tab,t_color *hit)
{
	double		f;
	int			octave;
	t_color hit1;

	octave = 1;
	f = 0.0;
	while (octave < 10)
	{
		f += (1.0f / octave) *\
		fabsf((float)(noise3(octave * intersect->vec3.x * 0.7,
			octave * intersect->vec3.y * 0.7, octave * intersect->vec3.z *
			0.7, perlin_tab)));
		octave++;
	}
	hit1.blue = (1.0 - f + 0.7 * f) * hit->blue;
	hit1.green = (1.0 - f + 0.7 * f) * hit->green;
	hit1.red = (1.0 - f + 0.7 * f) * hit->red;
	return (hit1);
}

t_color		makenoise_marble(t_cross *intersect, int *perlin_tab,t_color *hit)
{
	double		f;
	int			octave;
	t_color hit1;

	octave = 1;
	f = 0.0;
	while (octave < 10)
	{
		f += (1.0f / octave) *\
		fabsf((float)(noise3(octave * intersect->vec3.x * 0.7,
			octave * intersect->vec3.y * 0.7, octave * intersect->vec3.z *
			0.7, perlin_tab)));
		octave++;
	}
	f = 1 - sqrt(fabs(sin(2 * PI * f)));
	hit1.blue = (1.0 - f + 0.7 * f) * hit->blue;
	hit1.green = (1.0 - f + 0.7 * f) * hit->green;
	hit1.red = (1.0 - f + 0.7 * f) * hit->red;
	return (hit1);
}
