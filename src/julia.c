#include "fractol.h"

// Takes the given x and y values and applies
// them to the Julia formula.
int	julia(t_root *root, long double x, long double y)
{
	int			i;
	long double	new_x;
	long double	new_y;
	long double	x_temp;

	i = 0;
	new_x = x * root->r_screen.x_scale + root->r_screen.x_offset;
	new_y = y * root->r_screen.y_scale + root->r_screen.y_offset;
	while (new_x * new_x + new_y * new_y < 2 * 2 && i <= root->r_screen.iteri)
	{
		x_temp = new_x * new_x - new_y * new_y;
		new_y = 2 * new_x * new_y + root->r_julia.y;
		new_x = x_temp + root->r_julia.x;
		i++;
	}
	if (root->r_screen.color_type == 0)
		put_rainbow(root, x, y, i);
	else if (root->r_screen.color_type == 1)
		put_single_color(root, x, y, i);
	else if (root->r_screen.color_type == 2)
		put_black_to_white(root, x, y, i);
	return (SUCCESS);
}
