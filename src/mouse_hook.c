#include <fractol.h>

// zooms in by making the values smaller with
// a set amount of (ZOOM) defined in the headerfile.
static void	mouse_up(t_root *root)
{
	root->r_screen.zoom += 1;
	root->r_screen.y_scale /= ZOOM;
	root->r_screen.x_scale /= ZOOM;
	root->r_screen.x_offset /= ZOOM;
	root->r_screen.y_offset /= ZOOM;
}

// zooms out by making the values bigger with
// a set amount of (ZOOM) defined in the headerfile.
static void	mouse_down(t_root *root)
{
	root->r_screen.zoom -= 1;
	root->r_screen.y_scale *= ZOOM;
	root->r_screen.x_scale *= ZOOM;
	root->r_screen.x_offset *= ZOOM;
	root->r_screen.y_offset *= ZOOM;
}

// If a mouse button is used this function gets called.
// Depending on the (int button) value we know what button was used.
// MLX gives the x and y value of the position of the mouse 
// at the time of button press.
// Examples of mouse buttons: Scroll up and Scroll down.
void	scroll_hook(double xdelta, double ydelta, void *param)
{
	long double	x_start;
	long double	y_start;
	long double	x_new;
	long double	y_new;
	int32_t		x;
	int32_t		y;
	t_root		*root;

	(void)xdelta;
	root = (t_root *)param;
	mlx_get_mouse_pos(root->mlx, &x, &y);
	x_start = (long double)x * root->r_screen.x_scale + root->r_screen.x_offset;
	y_start = (long double)y * root->r_screen.y_scale + root->r_screen.y_offset;
	if (ydelta > 0)
		mouse_up(root);
	else if (ydelta < 0)
		mouse_down(root);
	x_new = (long double)x * root->r_screen.x_scale
		+ root->r_screen.x_offset;
	y_new = (long double)y * root->r_screen.y_scale
		+ root->r_screen.y_offset;
	x_new -= x_start;
	y_new -= y_start;
	root->r_screen.x_offset -= x_new;
	root->r_screen.y_offset -= y_new;
	change_image(root);
}
