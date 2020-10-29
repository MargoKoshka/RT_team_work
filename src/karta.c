
/*
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
​
#define WIDHT 1000
#define HIGHT 600
​
typedef struct  s_prog
{
  void *mlx_ptr;
  void *win_ptr;
  void *img_ptr;
  int *img_data;
  int bpp;
  int size_line;
  int endian;
  void *picture;
  // void *pict_data;
  unsigned int *pict_data;
  int pict_widht;
  int pict_higth;
  int pict_size_line;
  // int bpp;
  int pict_endian;
}t_prog;
​
void ft_put_pixel(int *img_data, int x, int y, int color)
{
  img_data[x + WIDHT * y] = color;
}
​
int   get_color(t_prog *data, int x, int y, int i)
{
​
  // return (*(unsigned int *)(data->pict_data + y * data->pict_size_line + x * 4));
  return (data->pict_data[y * data->pict_widht + x]);
}
​
int press(int key, t_prog *all)
{
  if (key == 53)
    exit(0);
  return(0);
}
​
int quit(void *param)
{
  (void)param;
  exit(1);
}
​
int main(int args, char **argv)
{
  t_prog a;
  int color;
  int x;
  int y;
  float k_width;
  float k_heith;
​
​
  a.mlx_ptr = mlx_init();
  a.win_ptr = mlx_new_window(a.mlx_ptr, WIDHT, HIGHT, "ku - ku");
  a.img_ptr = mlx_new_image(a.mlx_ptr, WIDHT, HIGHT);
  a.img_data = (int *)mlx_get_data_addr(a.img_ptr, &a.bpp, &a.size_line, &a.endian);
​
  a.picture = mlx_xpm_file_to_image(a.mlx_ptr, "./eath.xpm", &a.pict_widht, &a.pict_higth);
  printf("W- %d    H- %d\n", a.pict_widht, a.pict_higth);
  // a.pict_data = mlx_get_data_addr(a.picture, &a.bpp, &a.pict_size_line, &a.pict_endian);
  a.pict_data = (unsigned int *)mlx_get_data_addr(a.picture, &a.bpp, &a.pict_size_line, &a.pict_endian);
  printf("IMGsize- %d    PICTsize- %d\n", a.size_line, a.pict_size_line);
  printf("%d\n", (int)(255 * 0.8));
  k_width = (float)a.pict_widht / WIDHT;
  k_heith = (float)a.pict_higth / HIGHT;
  for (y = 0; y < HIGHT; y++)
  {
    for (x = 0; x < WIDHT; x++)
    {
      color = get_color(&a, x * k_width, y * k_heith, 0);
      ft_put_pixel(a.img_data, x, y, color);
    }
  }
  mlx_put_image_to_window(a.mlx_ptr, a.win_ptr, a.img_ptr, 0, 0);
  mlx_hook(a.win_ptr, 2, 0, press, (void *)&a);
  mlx_hook(a.win_ptr, 17, 0, quit, (void *)&a);
  mlx_loop(a.mlx_ptr);
​
  return (0);
}
​*/
// gcc new_pict.c -lmlx -framework OpenGL -framework AppKit














/*
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

int			err_malloc_texture(int *size, t_object *obj)
{
	ft_putstr_fd("Texture file data could not be loaded !\n", 2);
	free_size_obj(size, obj);
	return (0);
}

int		load_texture(t_rtv *e, t_object *object)
{
	void	*image;
	int		*imgstr;
	int		*size;
	int		a[3];

	if (!(size = get_xpm_size("xpm/earth.xpm", object)))
		return (0);
	object->texture_size = size;
	if (!(image = mlx_xpm_file_to_image(e->mlx_ptr,
					"xpm/earth.xpm", &size[0], &size[1])))
		return (err_malloc_texture(size, object));
	if (!(imgstr = (int *)mlx_get_data_addr(image, &a[0], &a[1], &a[2])))
		return (err_malloc_texture(size, object));
	if (!(object->texture_tab = color_tab(imgstr, size)))
		return (err_malloc_texture(object->texture_size , object));
	return (1);
}*/