/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hsv.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 17:43:57 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/11 15:07:49 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <hsv.h>

static void	rgb_to_hsv(t_hsv *hsv_data)
{
	hsv_data->v = fmaxf(hsv_data->r, hsv_data->g);
	hsv_data->v = fmaxf(hsv_data->v, hsv_data->b);
	hsv_data->x_max = hsv_data->v;
	hsv_data->x_min = fminf(hsv_data->r, hsv_data->g);
	hsv_data->x_min = fminf(hsv_data->x_min, hsv_data->b);
	hsv_data->c = hsv_data->x_max - hsv_data->x_min;
	if (hsv_data->c == 0)
		hsv_data->h = 0;
	else if (hsv_data->v == hsv_data->r)
		hsv_data->h = 1.0 / 6 * (0 + (hsv_data->g - hsv_data->b) / hsv_data->c);
	else if (hsv_data->v == hsv_data->g)
		hsv_data->h = 1.0 / 6 * (2 + (hsv_data->b - hsv_data->r) / hsv_data->c);
	else if (hsv_data->v == hsv_data->b)
		hsv_data->h = 1.0 / 6 * (4 + (hsv_data->r - hsv_data->g) / hsv_data->c);
	if (hsv_data->h < 0)
		hsv_data->h += 1;
	if (hsv_data->v == 0)
		hsv_data->s = 0;
	else
		hsv_data->s = hsv_data->c / hsv_data->v;
}

static void	set_hsv_values(t_hsv *hsv, float r1_v, float g1_v, float b1_v)
{
	hsv->r1 = r1_v;
	hsv->g1 = g1_v;
	hsv->b1 = b1_v;
	hsv->m = hsv->v - hsv->c;
	hsv->r = hsv->r1 + hsv->m;
	hsv->g = hsv->g1 + hsv->m;
	hsv->b = hsv->b1 + hsv->m;
}

static void	hsv_to_rgb(t_hsv *hsv)
{
	hsv->r1 = 0;
	hsv->g1 = 0;
	hsv->b1 = 0;
	hsv->h_priem = hsv->h / (1.0 / 6);
	hsv->c = hsv->v * hsv->s;
	hsv->x = hsv->c * (1 - fabs(fmod(hsv->h_priem, 2.0) - 1));
	if (0 <= hsv->h_priem && hsv->h_priem < 1)
		set_hsv_values(hsv, hsv->c, hsv->x, 0);
	else if (1 <= hsv->h_priem && hsv->h_priem < 2)
		set_hsv_values(hsv, hsv->x, hsv->g1, 0);
	else if (2 <= hsv->h_priem && hsv->h_priem < 3)
		set_hsv_values(hsv, 0, hsv->c, hsv->x);
	else if (3 <= hsv->h_priem && hsv->h_priem < 4)
		set_hsv_values(hsv, 0, hsv->x, hsv->c);
	else if (4 <= hsv->h_priem && hsv->h_priem < 5)
		set_hsv_values(hsv, hsv->x, 0, hsv->c);
	else if (5 <= hsv->h_priem && hsv->h_priem < 6)
		set_hsv_values(hsv, hsv->c, hsv->g1, hsv->x);
}

static void	split_rgb_hsv(unsigned base_color, t_hsv *hsv_data)
{
	hsv_data->r = (base_color >> 24 & 0xFF) / 255.0;
	hsv_data->g = (base_color >> 16 & 0xFF) / 255.0;
	hsv_data->b = (base_color >> 8 & 0xFF) / 255.0;
}

int32_t	get_rainbow_color(t_root *root, size_t i)
{
	t_hsv	hsv_data;

	hsv_data.h_increase = fmod(1.0 / 6.0 * (i % 255), 1.0);
	split_rgb_hsv(root->r_screen.color, &hsv_data);
	rgb_to_hsv(&hsv_data);
	hsv_data.h = fmod(hsv_data.h + hsv_data.h_increase * 255 / 4.0 + 1.0, 1.0);
	hsv_data.v = 1.0;
	if (hsv_data.s < 0.5)
		hsv_data.s = 0.5;
	hsv_to_rgb(&hsv_data);
	return (rgb_to_int(hsv_data.r * 255, hsv_data.g * 255, hsv_data.b * 255));
}
