#include <fractol.h>

// Keeps calulating the given X and Y values till the set max iterations,
// Unless it falls outside of the 2 * 2 threshold.
void	mandelbrot_helper(t_root *r, int *i, long double i_s, long double r_s)
{
	long double	rl;
	long double	im;
	long double	rl_tmp;

	rl = 0;
	im = 0;
	while (rl * rl + im * im <= 2 * 2 && *i <= r->r_screen.iteri)
	{
		rl_tmp = rl * rl - im * im + r_s;
		im = 2 * rl * im + i_s;
		rl = rl_tmp;
		*i += 1;
	}
}

// Sets the values X and Y to fit within the mandelbrot plot.
// Calls helper for the calculations.
// Can enable rainbow coloring mode by pressing <R> on the keyboard.
int	mandelbrot(t_root *root, long double x, long double y)
{
	int			i;
	long double	r_start;
	long double	i_start;

	i = 0;
	r_start = x * root->r_screen.x_scale + root->r_screen.x_offset;
	i_start = y * root->r_screen.y_scale + root->r_screen.y_offset;
	mandelbrot_helper(root, &i, i_start, r_start);
	if (root->r_screen.color_type == 0)
		put_rainbow(root, x, y, i);
	else if (root->r_screen.color_type == 1)
		put_single_color(root, x, y, i);
	else if (root->r_screen.color_type == 2)
		put_black_to_white(root, x, y, i);
	return (SUCCESS);
}
