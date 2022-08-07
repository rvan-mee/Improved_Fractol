/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:30:28 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/07 20:19:18 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

// Cycles through the colors initiated in the function init_colors (main.c).
static void	single_change_image(t_root *root)
{
	static int	i = 1;

	if (i > 5)
		i = 0;
	root->r_screen.all_options = i;
	i++;
}

// Checks what kind of color mode has to be used depending on what key is used 
// (rainbow or single).
// If pressed again will changed the current colors 
// apearing on screen in the selected mode.
static void	set_change_image_type(int key, t_root *root)
{
	static int	i;

	if (key == MLX_KEY_R)
	{
		if (i > 10)
			i = 0;
		root->r_screen.color_type = 0;
		root->r_screen.color = root->r_screen.rainbow_base[i];
		i++;
	}
	else if (key == MLX_KEY_C)
	{
		root->r_screen.color_type = 1;
		single_change_image(root);
	}
	else
		root->r_screen.color_type = 2;
}

// If page up or page down is used changes the iterations to be higher or lower.
static void	set_iteri(int key, t_root *root)
{
	if (key == MLX_KEY_PAGE_UP)
	{
		root->r_screen.iteri += 50;
		return ;
	}
	if (root->r_screen.iteri > 100)
		root->r_screen.iteri -= 50;
}

// Sets the offset of the arrow keys to be more user friendly depending 
// on the depth of the current zoom.
static long double	set_zoom_offset(t_root *root)
{
	long double	zoom_offset;

	zoom_offset = 1;
	if (root->r_screen.zoom <= 6 && root->r_screen.zoom != 0)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 50;
	else if (root->r_screen.zoom >= 7 && root->r_screen.zoom <= 9)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 125;
	else if (root->r_screen.zoom >= 10 && root->r_screen.zoom <= 13)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 5000;
	else if (root->r_screen.zoom >= 14 && root->r_screen.zoom <= 17)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 50000;
	else if (root->r_screen.zoom >= 18 && root->r_screen.zoom <= 22)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 3000000;
	else if (root->r_screen.zoom >= 23)
		zoom_offset = root->r_screen.zoom * root->r_screen.zoom * 250000000;
	return (zoom_offset);
}

// Function gets called whenever a key press is done within runtime.
// Checks what kind of key is used with the given (int key) value and
// calls the assigned function or adjusts a certain value.
// Examples of keys that can be used: page up & down, arrow keys, C and R.
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_root		*root;
	const int	key = keydata.key;

	root = (t_root *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);
	else if (key == DOWN && keydata.action == PRESS && root->set != MOUSE)
		root->r_screen.y_offset -= (long double)OFFSET / set_zoom_offset(root);
	else if (key == UP && keydata.action == PRESS && root->set != MOUSE)
		root->r_screen.y_offset += (long double)OFFSET / set_zoom_offset(root);
	else if (key == LEFT && keydata.action == PRESS && root->set != MOUSE)
		root->r_screen.x_offset -= (long double)OFFSET / set_zoom_offset(root);
	else if (key == RIGHT && keydata.action == PRESS && root->set != MOUSE)
		root->r_screen.x_offset += (long double)OFFSET / set_zoom_offset(root);
	else if (keydata.action == PRESS && (key == C || key == B || \
			(key == R && root->set != MOUSE)))
		set_change_image_type(keydata.key, root);
	else if ((key == P_UP || \
			key == P_DOWN) && keydata.action == PRESS)
		set_iteri(key, root);
	if ((key == RIGHT || key == LEFT || key == DOWN || key == UP \
		|| key == R || key == C || key == P_DOWN || key == P_UP \
		|| key == B) && keydata.action == PRESS)
		update_image(root);
}
