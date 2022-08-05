/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_set.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 15:41:04 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/05 18:55:31 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdlib.h>

void	mouse_hook(void *param)
{
	t_root *const	root = param;
	static bool		mouse_down = false;
	int32_t			x;
	int32_t			y;

	mlx_get_mouse_pos(root->mlx, &x, &y);
	y -= HEIGHT;
	root->r_julia.x = x * root->r_screen.x_scale + root->r_screen.x_offset;
	root->r_julia.y = y * root->r_screen.y_scale + root->r_screen.y_offset;
	if (mlx_is_mouse_down(root->mlx, MLX_MOUSE_BUTTON_LEFT) && mouse_down == false)
	{
		printf("Current julia input: %.3Lf + %.3Lfi\n", root->r_julia.x, root->r_julia.y);
		mouse_down = true;
	}
	if (mlx_is_mouse_down(root->mlx, MLX_MOUSE_BUTTON_LEFT) == false)
		mouse_down = false;
	update_image(root);
}

void	create_mandelbrot_picture(t_root *root)
{
	long double	r_start;
	long double	i_start;
	double		pei;
	int32_t		i;
	int32_t		x;
	int32_t		y;

	x = 0;
	root->mouse_mandelbrot_img = mlx_new_image(root->mlx, WIDTH, HEIGHT);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			i = 0;
			r_start = x * root->r_screen.x_scale + root->r_screen.x_offset;
			i_start = y * root->r_screen.y_scale + root->r_screen.y_offset;
			mandelbrot_helper(root, &i, i_start, r_start);
			pei = (double)i / root->r_screen.iteri * 255;
			if (i == root->r_screen.iteri + 1)
				mlx_put_pixel(root->mouse_mandelbrot_img, x, y, 255);
			else
				mlx_put_pixel(root->mouse_mandelbrot_img, x, y, color(1 * pei, 0, 0));
			y++;
		}
		x++;
	}
	mlx_image_to_window(root->mlx, root->mouse_mandelbrot_img, 0, HEIGHT);
}
