/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 14:23:46 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/11 14:19:40 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <stdio.h>
# include <stdint.h>

# define RGB 3
# define FILE_TYPE 0x4d42
# define HEADER_SIZE 54
# define DIB_HEADER_SIZE 40
# define COLOR_PLANES_COUNT 1
# define BITS_PER_PIXEL 24

typedef struct s_bm_data {
	int32_t			padding;
	int32_t			line_size;
	int32_t			data_size;
	unsigned char	*data;
}	t_bmp_data;

typedef struct s_bmp_file_header {
	uint16_t	type;
	uint32_t	size;
	uint16_t	app_specific_unused;
	uint16_t	app_specific_unused2;
	uint32_t	header_offset;
	uint32_t	dib_header_size;
	int32_t		width_pixels;
	int32_t		height_pixels;
	uint16_t	color_planes;
	uint16_t	bits_per_pixel;
	uint32_t	pixel_array_compression;
	uint32_t	image_size_bytes;
	int32_t		x_resolution_ppm;
	int32_t		y_resolution_ppm;
	uint32_t	num_colors;
	uint32_t	important_colors;
} __attribute__((packed))t_bmp_file_header;

#endif
