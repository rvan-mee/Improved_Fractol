/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_set.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 15:41:04 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/04 18:02:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdlib.h>

void	mouse_hook(void *param)
{
	t_root *const	root = param;
	int32_t			x;
	int32_t			y;

	mlx_get_mouse_pos(root->mlx, &x, &y);
	root->r_julia.x = x * root->r_screen.x_scale + root->r_screen.x_offset;
	root->r_julia.y = y * root->r_screen.y_scale + root->r_screen.y_offset;
	// printf("mouse position: %Lf %Lf\n", root->r_julia.x, root->r_julia.y);
	update_image(root);
}
