#include "fractol.h"

int32_t	WIDTH = 1920;
int32_t	HEIGHT = 1080;

// Initiate all the base colors for the rainbow mode.
static void	init_rainbow_colors(t_root *root)
{
	root->r_screen.rainbow_base[0] = 0x0000F00FF;
	root->r_screen.rainbow_base[1] = 0x00F00F0FF;
	root->r_screen.rainbow_base[2] = 0x0000000FF;
	root->r_screen.rainbow_base[3] = 0x000FFFFFF;
	root->r_screen.rainbow_base[4] = 0x00000FFFF;
	root->r_screen.rainbow_base[5] = 0x000FFFFFF;
	root->r_screen.rainbow_base[6] = 0x000FF00FF;
	root->r_screen.rainbow_base[7] = 0x0000F00FF;
	root->r_screen.rainbow_base[8] = 0x00020F6DA;
	root->r_screen.rainbow_base[9] = 0x00000277D;
	root->r_screen.rainbow_base[10] = 0x000F00FF;
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
	root->mlx = mlx_init(WIDTH, HEIGHT, "fract-ol", true);
	if (root->set == MOUSE)
		HEIGHT /= 2;
	if (root->mlx == NULL)
		exit_error("MLX error\n");
	root->r_screen.iteri = 100;
	root->r_screen.x_scale = 2 / (long double)HEIGHT;
	root->img = mlx_new_image(root->mlx, WIDTH, HEIGHT);
	root->r_screen.y_scale = 2 / (long double)HEIGHT * -1;
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
		create_mandelbrot_picture(&root);
		mlx_loop_hook(root.mlx, mouse_hook, &root);
	}
	mlx_loop(root.mlx);
	mlx_delete_image(root.mlx, root.img);
	mlx_terminate(root.mlx);
	return (0);
}
