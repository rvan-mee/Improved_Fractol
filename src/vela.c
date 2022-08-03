#include "fractol.h"

// Keeps calulating the given X and Y values till the set max iterations,
// Unless it falls outside of the 4 threshold.
static void	ship_helper(t_root *r, int *i, long double i_y, long double r_x)
{
	long double	zx;
	long double	zy;
	long double	x_temp;

	zx = r_x;
	zy = i_y;
	while (zx * zx + zy * zy < 4 && *i <= r->r_screen.iteri)
	{
		x_temp = zx * zx - zy * zy + r_x;
		zy = fabsl(2 * zx * zy) + i_y;
		zx = x_temp;
		*i += 1;
	}
}

// Sets the values X and Y to fit within the burning ship plot.
// Calls helper for the calculations.
int	burning_ship(t_root *root, long double x, long double y)
{
	int			i;
	long double	r_start;
	long double	i_start;

	i = 0;
	r_start = x * root->r_screen.x_scale + root->r_screen.x_offset;
	i_start = (y * root->r_screen.y_scale + root->r_screen.y_offset) * -1;
	ship_helper(root, &i, i_start, r_start);
	if (root->r_screen.color_type == 0)
		put_rainbow(root, x, y, i);
	else if (root->r_screen.color_type == 1)
		put_single_color(root, x, y, i);
	else if (root->r_screen.color_type == 2)
		put_black_to_white(root, x, y, i);
	return (SUCCESS);
}
