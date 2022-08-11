/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:03:37 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/11 13:08:28 by rvan-mee      ########   odam.nl         */
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
#  define THREADS 24
# endif

# define FAIL 0
# define SUCCESS 1
# define OFFSET 1
# define ZOOM 3
# define CHECK_I 1
# define DONT_CHECK_I 0

# define DOWN MLX_KEY_DOWN
# define UP MLX_KEY_UP
# define LEFT MLX_KEY_LEFT
# define RIGHT MLX_KEY_RIGHT
# define PRESS MLX_PRESS
# define P MLX_KEY_P
# define C MLX_KEY_C
# define B MLX_KEY_B
# define R MLX_KEY_R
# define P_DOWN MLX_KEY_PAGE_DOWN
# define P_UP MLX_KEY_PAGE_UP

typedef enum sets
{
	MANDELBROT,
	JULIA,
	VELA,
	MOUSE
}	t_sets;

typedef struct s_julia {
	long double	x;
	long double	y;
}	t_julia;

typedef struct rgb
{
	int8_t	red;
	int8_t	green;
	int8_t	blue;
}	t_rgb;

typedef struct s_screen {
	int32_t		color;
	int32_t		all_options;
	int32_t		options[7][3];
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
	uint32_t		width;
	uint32_t		height;
	t_screen		r_screen;
	t_julia			r_julia;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*mandelbrot_img;
	pthread_mutex_t	image_mutex;
	int32_t			set;
	int32_t			y;
}	t_root;

typedef struct s_mandel {
	long double	r_start;
	long double	i_start;
	double		pei;
	int32_t		i;
	uint32_t	x;
	uint32_t	y;
}	t_mandel;

typedef struct s_drag {
	long double	old_x;
	long double	old_y;
	long double	curr_x;
	long double	curr_y;
	bool		previous_mouse_down;
	bool		is_mouse_down;
	int			y;
	int			x;
}	t_drag;

typedef struct s_scroll {
	long double	x_start;
	long double	y_start;
	long double	x_new;
	long double	y_new;
	int32_t		x;
	int32_t		y;
}	t_scroll;

typedef struct s_hsv {
	float	h_increase;
	float	h_priem;
	float	r;
	float	g;
	float	b;
	float	h;
	float	s;
	float	v;	
	float	c;
	float	m;
	float	x;
	float	r1;
	float	g1;
	float	b1;
	float	x_min;
	float	x_max;
}	t_hsv;

int			main(int argc, char *argv[]);
void		exit_error(char *error_message);
void		check_input(int argc, char **argv, t_root *root);
void		key_hook(mlx_key_data_t keydata, void *param);
void		scroll_hook(double xdelta, double ydelta, void *param);

void		update_image(t_root *root);
void		init_mutexes(t_root *root);

void		create_picture(t_root *root);

int			rgb_to_int(int r, int g, int b);
t_rgb		split_rgb(int32_t base_color);
int32_t		get_rainbow_color(t_root *root, size_t i);
void		put_rainbow(t_root *root, int x, int y, int i);
void		put_black_to_white(t_root *root, int x, int y, int i);
void		put_single_color(t_root *root, int x, int y, int i);

int			mandelbrot(t_root *root, long double x, long double y);
void		mandelbrot_helper(t_root *r, int *i, \
							long double i_s, long double r_s);
int			burning_ship(t_root *root, long double x, long double y);
int			julia(t_root *root, long double x, long double y);

void		drag_hook(void *param);
void		mouse_hook(void *param);
void		update_mandelbrot_picture(t_root *root);

void		*update_fractal(void *param);

long double	ft_atof(char *str, int i_check);
long double	ft_atosign(char *sign);

#endif
