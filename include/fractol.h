/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:03:37 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/04 14:02:02 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include "MLX42/MLX42.h"

# ifndef THREADS
# define THREADS 4
# endif

# define WIDTH 1920
# define HEIGHT 1080 
# define FAIL 0
# define SUCCESS 1
# define OFFSET 1
# define ZOOM 3
# define CHECK_I 1
# define DONT_CHECK_I 0

typedef struct s_julia {
	long double	x;
	long double	y;
}	t_julia;

typedef struct s_screen {
	int32_t		color;
	int32_t		all_options;
	int32_t		options[7][3];
	int32_t		rainbow_base[11];
	int32_t		color_type;
	int32_t		iteri;
	long double	x_scale;
	long double	y_scale;
	long double	x_offset;
	long double	y_offset;
	long double	zoom;
	long double	escape;
}	t_screen;

typedef struct s_root {
	t_screen		r_screen;
	t_julia			r_julia;
	mlx_t			*mlx;
	mlx_image_t		*img;
	pthread_mutex_t	image_mutex;
	int32_t			set;
	int32_t			y;
}	t_root;

int			main(int argc, char *argv[]);
void		exit_error(char *error_message);
void		check_input(int argc, char **argv, t_root *root);
void		key_hook(mlx_key_data_t keydata, void *param);
void		scroll_hook(double xdelta, double ydelta, void *param);

void		update_image(t_root *root);
void		init_mutexes(t_root *root);

void		put_rainbow(t_root *root, int x, int y, int i);
void		put_black_to_white(t_root *root, int x, int y, int i);
void		put_single_color(t_root *root, int x, int y, int i);

int			mandelbrot(t_root *root, long double x, long double y);
int			burning_ship(t_root *root, long double x, long double y);
int			julia(t_root *root, long double x, long double y);
void		*change_image(void *param);

long double	ft_atof(char *str, int i_check);
long double	ft_atosign(char *sign);

#endif
