#include "fractol.h"

// Applies the correct funtion to the pixel given the command line input.
static void	fractal(t_root *root, int x, int y)
{
	if (root->set == 1)
		mandelbrot(root, x, y);
	else if (root->set == 2)
		julia(root, x, y);
	else if (root->set == 3)
		burning_ship(root, x, y);
}

// Loops through all the possible pixels given the set 
// (HEIGHT) and (WIDTH) defined in the headerfile.
void	change_image(t_root *root)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		fractal(root, x, y);
		while (x < WIDTH)
		{
			fractal(root, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}
