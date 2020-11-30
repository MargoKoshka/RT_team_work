/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot_bmp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:26:40 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 14:34:04 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define BMP_HEADER_SIZE 14
#define BMP_INFO_SIZE (OFFSET - BMP_HEADER_SIZE)
#define OFFSET 54
#define PLANES 1

char	*create_name_file(const char *name, const char *type)
{
	char		*file_name;
	char		*tmp_name;

	tmp_name = ft_strsub(name, 0, ft_strlen(name) - 5);
	file_name = ft_strjoin("screen_", tmp_name);
	free(tmp_name);
	tmp_name = NULL;
	tmp_name = file_name;
	file_name = ft_strjoin(tmp_name, type);
	free(tmp_name);
	tmp_name = NULL;
	return (file_name);
}

void	copy_pixel_bmp(unsigned char *image, int *color, size_t num)
{
	size_t	n;

	n = 0;
	while (n < num)
	{
		image[n * 4 + 3] = (unsigned char)(0x00);
		image[n * 4 + 2] = (unsigned char)((color[n] >> 16) & 0xFF);
		image[n * 4 + 1] = (unsigned char)((color[n] >> 8) & 0xFF);
		image[n * 4 + 0] = (unsigned char)(color[n] & 0xFF);
		n += 1;
	}
}

void	create_header_bmp(t_rtv *paint, char *bmp, int file_size)
{
	ft_memcpy(bmp, "BM", 2);
	*(unsigned int *)(bmp + 2) = file_size;
	*(unsigned int *)(bmp + 10) = OFFSET;
	*(unsigned int *)(bmp + 14) = BMP_INFO_SIZE;
	*(unsigned int *)(bmp + 18) = paint->width;
	*(unsigned int *)(bmp + 22) = -paint->height;
	*(unsigned short *)(bmp + 26) = PLANES;
	*(unsigned short *)(bmp + 28) = (short)paint->bpp;
}

void	save_bmp_file(t_rtv *paint)
{
	unsigned char	image[paint->width * paint->height * 4];
	int				fd;
	int				file_size;
	char			*bmp;
	char			*file_name;

	file_name = NULL;
	file_name = create_name_file(paint->name_file, ".bmp");
	if ((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) > 0)
	{
		if ((bmp = malloc(OFFSET)))
		{
			ft_bzero(bmp, OFFSET);
			file_size = paint->width * paint->height * 4 + OFFSET;
			create_header_bmp(paint, bmp, file_size);
			copy_pixel_bmp(image, paint->draw, paint->width * paint->height);
			write(fd, bmp, OFFSET);
			write(fd, image, paint->width * paint->height * 4);
			free(file_name);
			free(bmp);
			close(fd);
			write(1, "Image saved\n", 12);
		}
	}
}
