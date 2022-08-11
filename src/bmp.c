/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/08 19:15:41 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/11 14:43:59 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <bmp.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

static int32_t	write_bmp_header(int32_t fd, t_root *root, t_bmp_data bmp_data)
{
	static t_bmp_file_header	header;

	header.type = FILE_TYPE;
	header.size = (root->height * root->width * sizeof(int32_t)) + HEADER_SIZE;
	header.header_offset = HEADER_SIZE;
	header.dib_header_size = DIB_HEADER_SIZE;
	header.width_pixels = root->width;
	header.height_pixels = root->height;
	header.color_planes = COLOR_PLANES_COUNT;
	header.bits_per_pixel = BITS_PER_PIXEL;
	header.image_size_bytes = bmp_data.data_size;
	if (write(fd, &header, sizeof(t_bmp_file_header)) == -1)
	{
		printf("error: %s\n", strerror(errno));
		fprintf(stderr, "Writing to BMP file failed\n");
		return (-1);
	}
	return (0);
}

static int32_t	create_new_bmp_file(t_root *root)
{
	int32_t				fd;
	char				*filename;
	static const char	*sets[] = {
		"mandelbrot",
		"Julia",
		"Burning_Ship",
		"Mouse"
	};

	asprintf(&filename, "fractol_%s_color:0x%x_offset:\
%Lf_Coords:%Lf_Zoom:%Lf.bmp", sets[root->set], root->r_screen.color, \
root->r_screen.x_offset, root->r_screen.y_offset, root->r_screen.zoom);
	fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0664);
	free(filename);
	if (fd == -1)
	{
		fprintf(stderr, "error: %s\n", strerror(errno));
		fprintf(stderr, "Creating BMP file failed\n");
	}
	return (fd);
}

static t_rgb	get_pixel_color(t_root *root, int32_t x, int32_t y)
{
	t_rgb	color;
	int8_t	*pixel_address;

	pixel_address = (int8_t *)&root->img->pixels[(y * root->width + x) \
						* sizeof(int32_t)];
	color.blue = *(pixel_address++);
	color.green = *(pixel_address++);
	color.red = *(pixel_address++);
	return (color);
}

static void	write_color_data(int32_t fd, t_root *root, t_bmp_data data)
{
	t_rgb			colors;
	uint32_t		x;
	uint32_t		y;
	size_t			i;

	i = 0;
	y = root->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < root->width)
		{
			colors = get_pixel_color(root, x, y);
			data.data[i++] = (unsigned char)colors.red;
			data.data[i++] = (unsigned char)colors.green;
			data.data[i++] = (unsigned char)colors.blue;
			x++;
		}
		if (y == 0)
			break ;
		y--;
	}
	if (write(fd, data.data, data.data_size) == -1)
		fprintf(stderr, "error: %s\n\
Writing to BMP file failed\n", strerror(errno));
	free(data.data);
}

void	create_picture(t_root *root)
{
	int32_t		fd;
	t_bmp_data	data;

	fd = create_new_bmp_file(root);
	if (fd == -1)
		return ;
	data.padding = root->width % sizeof(int32_t);
	data.line_size = RGB * root->width + data.padding;
	data.data_size = data.line_size * root->height;
	data.data = calloc(data.data_size, sizeof(unsigned char));
	if (!data.data)
		exit_error("Failed to allocate memory inside create_picture\n");
	if (write_bmp_header(fd, root, data) == -1)
		return ;
	write_color_data(fd, root, data);
	close(fd);
}
