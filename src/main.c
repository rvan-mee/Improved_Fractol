/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:26:20 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/07 20:18:09 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Initiate all the base colors for the rainbow mode.
static void	init_rainbow_colors(t_root *root)
{
	root->r_screen.rainbow_base[0] = 0x2CDDB2FF;
	root->r_screen.rainbow_base[1] = 0x00FF00FF;
	root->r_screen.rainbow_base[2] = 0x0000FFFF;
	root->r_screen.rainbow_base[3] = 0x00FFFFFF;
	root->r_screen.rainbow_base[4] = 0xFF00FFFF;
	root->r_screen.rainbow_base[5] = 0xFFFF00FF;
	root->r_screen.rainbow_base[6] = 0xFF0000FF;
	root->r_screen.rainbow_base[7] = 0xF59DAFFF;
	root->r_screen.rainbow_base[8] = 0xE71BD6FF;
	root->r_screen.rainbow_base[9] = 0x33D1C6FF;
	root->r_screen.rainbow_base[10] = 0xF1EE2CFF;
}

// Initiate all the color options.
static void	init_options(t_root *root)
{
	root->r_screen.all_options = 0;
	root->r_screen.options[0][0] = 1;
	root->r_screen.options[0][1] = 0;
	root->r_screen.options[0][2] = 0;
	root->r_screen.options[1][0] = 0;
	root->r_screen.options[1][1] = 1;
	root->r_screen.options[1][2] = 0;
	root->r_screen.options[2][0] = 0;
	root->r_screen.options[2][1] = 0;
	root->r_screen.options[2][2] = 1;
	root->r_screen.options[3][0] = 1;
	root->r_screen.options[3][1] = 1;
	root->r_screen.options[3][2] = 0;
	root->r_screen.options[4][0] = 1;
	root->r_screen.options[4][1] = 0;
	root->r_screen.options[4][2] = 1;
	root->r_screen.options[5][0] = 0;
	root->r_screen.options[5][1] = 1;
	root->r_screen.options[5][2] = 1;
}

// Initiate all the MLX data and screen data.
static int	init_mlx(t_root *root)
{
	init_options(root);
	init_rainbow_colors(root);
	root->mlx = mlx_init(root->width, root->height, "fract-ol", true);
	if (root->set == MOUSE)
		root->height /= 2;
	if (root->mlx == NULL)
		exit_error("MLX error\n");
	root->r_screen.iteri = 100;
	root->r_screen.x_scale = 2 / (long double)root->height;
	root->img = mlx_new_image(root->mlx, root->width, root->height);
	root->r_screen.y_scale = 2 / (long double)root->height * -1;
	root->r_screen.x_offset = -2;
	root->r_screen.y_offset = 1;
	root->r_screen.zoom = 0;
	root->r_screen.color = 0x0000FFFF;
	root->r_screen.color_type = 1;
	if (root->img == NULL)
		exit_error("MLX error\n");
	if (mlx_image_to_window(root->mlx, root->img, 0, 0) == -1)
		exit_error("MLX error\n");
	return (0);
}

// initiates all the values to have 
// the burning ship fractol in a better position.
static void	init_ship(t_root *root)
{
	root->r_screen.zoom = 3;
	root->r_screen.x_scale = 0.00012056327160493829;
	root->r_screen.y_scale = -0.00014288980338363055;
	root->r_screen.x_offset = -1.79834876543209878344;
	root->r_screen.y_offset = 0.10413351623228167290;
}

// Calls the init functions and starts the MLX loop.
int	main(int argc, char *argv[])
{
	t_root	root;

	check_input(argc, argv, &root);
	init_mutexes(&root);
	init_mlx(&root);
	if (root.set == VELA)
		init_ship(&root);
	mlx_key_hook(root.mlx, &key_hook, &root);
	if (root.set != MOUSE)
	{
		update_image(&root);
		mlx_loop_hook(root.mlx, &drag_hook, &root);
		mlx_scroll_hook(root.mlx, &scroll_hook, &root);
	}
	else
	{
		root.mandelbrot_img = mlx_new_image(root.mlx, root.width, root.height);
		mlx_image_to_window(root.mlx, root.mandelbrot_img, 0, root.height);
		create_mandelbrot_picture(&root);
		mlx_loop_hook(root.mlx, mouse_hook, &root);
	}
	mlx_loop(root.mlx);
	mlx_delete_image(root.mlx, root.img);
	mlx_terminate(root.mlx);
	return (0);
}
