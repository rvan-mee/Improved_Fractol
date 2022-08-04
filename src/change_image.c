/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_image.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 13:27:09 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/04 17:07:01 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Applies the correct funtion to the pixel given the command line input.
static void	fractal(t_root *root, int x, int y)
{
	if (root->set == MANDELBROT)
		mandelbrot(root, x, y);
	else if (root->set == JULIA || root->set == MOUSE)
		julia(root, x, y);
	else if (root->set == VELA)
		burning_ship(root, x, y);
}

// Loops through all the possible pixels given the set 
// (HEIGHT) and (WIDTH) defined in the headerfile.
void	*change_image(void *param)
{
	t_root	*root;
	int		x;
	int		y;

	root = param;
	x = 0;
	pthread_mutex_lock(&root->image_mutex);
	y = root->y;
	root->y += 1;
	pthread_mutex_unlock(&root->image_mutex);
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			fractal(root, x, y);
			x++;
		}
		x = 0;
		pthread_mutex_lock(&root->image_mutex);
		y = root->y;
		root->y += 1;
		pthread_mutex_unlock(&root->image_mutex);
	}
	return (NULL);
}
