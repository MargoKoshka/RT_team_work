#include "rtv1.h"

/* 
**Output data as PPM file
*/

void	save_ppm_file(char *file_name, t_rtv *paint, unsigned char *img)
{
	/* FILE pointer */
	int	fd;

	/* Open file for writing */
	if ((fd = open(file_name, O_WRONLY)) <= 0)
		ft_exit(ERR_FILE_OPEN);
	
	/* PPM header info, including the size of the image */
	fprintf(fd, "P6 %d %d %d\n", paint->width, paint->height, 255);

	/* Write the image data to the file - remember 3 byte per pixel */
	write(fd, img, paint->width * paint->height);

	/* Make sure you close the file */
	close(fd);
}

