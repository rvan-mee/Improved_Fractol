/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_set.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 15:41:04 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/07 13:50:26 by rvan-mee      ########   odam.nl         */
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
	y -= root->height;
	root->r_julia.x = x * root->r_screen.x_scale + root->r_screen.x_offset;
	root->r_julia.y = y * root->r_screen.y_scale + root->r_screen.y_offset;
	if (mlx_is_mouse_down(root->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& mouse_down == false)
	{
		printf("Current julia input: real: %.3Lf imaginary: %.3Lfi\n", \
										root->r_julia.x, root->r_julia.y);
		mouse_down = true;
	}
	if (mlx_is_mouse_down(root->mlx, MLX_MOUSE_BUTTON_LEFT) == false)
		mouse_down = false;
	update_image(root);
}

static void	put_black_white_mouse(t_root *root, int x, int y, int i)
{
	double	pei;

	pei = (double)i / root->r_screen.iteri * 255;
	if (i == root->r_screen.iteri + 1)
	{
		mlx_put_pixel(root->mandelbrot_img, x, y, 0xFFFFFFFF);
		return ;
	}
	mlx_put_pixel(root->mandelbrot_img, x, y, color(pei, pei, pei));
}

static void	put_single_color_mouse(t_root *root, int x, int y, int i)
{
	int			j;
	double		pei;

	j = root->r_screen.all_options;
	pei = (double)i / root->r_screen.iteri * 255;
	if (i == root->r_screen.iteri + 1)
		mlx_put_pixel(root->mandelbrot_img, x, y, 255);
	else
	{
		mlx_put_pixel(root->mandelbrot_img, x, y,
			color(root->r_screen.options[j][0] * pei,
				root->r_screen.options[j][1] * pei,
				root->r_screen.options[j][2] * pei));
	}
}

void	create_mandelbrot_picture(t_root *root)
{
	t_mandel	mandel;

	mandel.x = 0;
	while (mandel.x < root->width)
	{
		mandel.y = 0;
		while (mandel.y < root->height)
		{
			mandel.i = 0;
			mandel.r_start = mandel.x * \
			root->r_screen.x_scale + root->r_screen.x_offset;
			mandel.i_start = mandel.y * \
			root->r_screen.y_scale + root->r_screen.y_offset;
			mandelbrot_helper(root, &mandel.i, mandel.i_start, mandel.r_start);
			mandel.pei = (double)mandel.i / root->r_screen.iteri * 255;
			if (root->r_screen.color_type == 1)
				put_single_color_mouse(root, mandel.x, mandel.y, mandel.i);
			else if (root->r_screen.color_type == 2)
				put_black_white_mouse(root, mandel.x, mandel.y, mandel.i);
			mandel.y++;
		}
		mandel.x++;
	}
}
