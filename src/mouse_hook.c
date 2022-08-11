/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_hook.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 14:12:08 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/11 15:05:23 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <mouse.h>

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
	t_scroll	scroll;
	t_root		*root;

	(void)xdelta;
	root = (t_root *)param;
	mlx_get_mouse_pos(root->mlx, &scroll.x, &scroll.y);
	scroll.x_start = (long double)scroll.x * \
	root->r_screen.x_scale + root->r_screen.x_offset;
	scroll.y_start = (long double)scroll.y * \
	root->r_screen.y_scale + root->r_screen.y_offset;
	if (ydelta > 0)
		mouse_up(root);
	else if (ydelta < 0)
		mouse_down(root);
	scroll.x_new = (long double)scroll.x * root->r_screen.x_scale
		+ root->r_screen.x_offset;
	scroll.y_new = (long double)scroll.y * root->r_screen.y_scale
		+ root->r_screen.y_offset;
	scroll.x_new -= scroll.x_start;
	scroll.y_new -= scroll.y_start;
	root->r_screen.x_offset -= scroll.x_new;
	root->r_screen.y_offset -= scroll.y_new;
	update_image(root);
}

void	drag_hook(void *param)
{
	t_root *const	root = param;
	static t_drag	drag;

	drag.is_mouse_down = mlx_is_mouse_down(root->mlx, MLX_MOUSE_BUTTON_LEFT);
	if (drag.is_mouse_down == true && drag.previous_mouse_down == false)
	{
		drag.previous_mouse_down = true;
		mlx_get_mouse_pos(root->mlx, &drag.x, &drag.y);
		drag.old_x = (long double)drag.x * \
		root->r_screen.x_scale + root->r_screen.x_offset;
		drag.old_y = (long double)drag.y * \
		root->r_screen.y_scale + root->r_screen.y_offset;
	}
	else if (drag.is_mouse_down == false && drag.previous_mouse_down == true)
	{
		drag.previous_mouse_down = false;
		mlx_get_mouse_pos(root->mlx, &drag.x, &drag.y);
		drag.curr_x = (long double)drag.x * root->r_screen.x_scale
			+ root->r_screen.x_offset;
		drag.curr_y = (long double)drag.y * root->r_screen.y_scale
			+ root->r_screen.y_offset;
		root->r_screen.x_offset += drag.old_x - drag.curr_x;
		root->r_screen.y_offset += drag.old_y - drag.curr_y;
		update_image(root);
	}
}
