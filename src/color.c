/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:39:30 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/10 13:53:11 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Returns a color's RGB value based on the input R G and B.
// Max values should be 255 per color.
int	rgb_to_int(int r, int g, int b)
{
	return ((r << 24 | g << 16 | b << 8) + 255);
}

t_rgb	split_rgb(int32_t base_color)
{
	t_rgb	rgb;

	rgb.red = base_color >> 24 & 0xFF;
	rgb.green = base_color >> 16 & 0xFF;
	rgb.blue = base_color >> 8 & 0xFF;
	return (rgb);
}

// Depending on the Iterations vs Max Iterations sets the color to black
// or sets the color to change in a much more rapid way then the single 
// version of this function.
void	put_rainbow(t_root *root, int x, int y, int i)
{
	int		new_color;

	new_color = 0;
	if (i == root->r_screen.iteri + 1)
	{
		mlx_put_pixel(root->img, x, y, 255);
		return ;
	}
	new_color = get_rainbow_color(root, i);
	if (new_color < 0xFFF)
		new_color += 0x0F0F0FFF;
	mlx_put_pixel(root->img, x, y, new_color);
}

// Scales from black to white.
// (pei) is the % of the current iteration compared to
// the max iteration, scaled to 255.
void	put_black_to_white(t_root *root, int x, int y, int i)
{
	double	pei;

	pei = (double)i / root->r_screen.iteri * 255;
	if (i == root->r_screen.iteri + 1)
	{
		mlx_put_pixel(root->img, x, y, 0xFFFFFFFF);
		return ;
	}
	mlx_put_pixel(root->img, x, y, rgb_to_int(pei, pei, pei));
}

// Depending on the Iterations vs Max Iterations sets the color to black
// or a color thats based off the current selected color (change by pressing C).
void	put_single_color(t_root *root, int x, int y, int i)
{
	int			j;
	double		pei;

	j = root->r_screen.all_options;
	pei = (double)i / root->r_screen.iteri * 255;
	if (i == root->r_screen.iteri + 1)
		mlx_put_pixel(root->img, x, y, 255);
	else
	{
		mlx_put_pixel(root->img, x, y,
			rgb_to_int(root->r_screen.options[j][0] * pei,
				root->r_screen.options[j][1] * pei,
				root->r_screen.options[j][2] * pei));
	}
}
