/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot_ppm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:26:46 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:26:47 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	copy_pixel_ppm(unsigned char *image, int *color, size_t num)
{
	size_t	n;

	n = 0;
	while (n < num)
	{
		image[n * 3 + 0] = (unsigned char)((color[n] >> 16) & 0xFF);
		image[n * 3 + 1] = (unsigned char)((color[n] >> 8) & 0xFF);
		image[n * 3 + 2] = (unsigned char)(color[n] & 0xFF);
		n += 1;
	}
}

/*
** PPM header info, including the size of the image
** "P6 %d %d %d\n", paint->width, paint->height, 255
*/

void	create_header_ppm(t_rtv *paint, int fd)
{
	char	*num_width;
	char	*num_heigth;

	num_width = ft_itoa(paint->width);
	num_heigth = ft_itoa(paint->height);
	ft_putstr_fd("P6 ", fd);
	ft_putstr_fd(num_width, fd);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(num_heigth, fd);
	ft_putendl_fd(" 255", fd);
	free(num_width);
	free(num_heigth);
}

/*
** PPM header info, including the size of the image
** Write the image data to the file - remember 3 byte per pixel
*/

void	save_ppm_file(t_rtv *paint)
{
	int				fd;
	unsigned char	image[paint->width * paint->height * 3];
	char			*file_name;

	file_name = NULL;
	file_name = create_name_file(paint->name_file, ".ppm");
	if ((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) <= 0)
		ft_exit(ERR_FILE_OPEN);
	copy_pixel_ppm(image, paint->draw, paint->width * paint->height);
	create_header_ppm(paint, fd);
	write(fd, image, paint->width * paint->height * 3);
	free(file_name);
	close(fd);
}
