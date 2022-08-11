/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 15:03:25 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/11 15:05:11 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MOUSE_H
# define MOUSE_H

# include <stdint.h>

typedef struct s_drag {
	long double	old_x;
	long double	old_y;
	long double	curr_x;
	long double	curr_y;
	bool		previous_mouse_down;
	bool		is_mouse_down;
	int			y;
	int			x;
}	t_drag;

typedef struct s_scroll {
	long double	x_start;
	long double	y_start;
	long double	x_new;
	long double	y_new;
	int32_t		x;
	int32_t		y;
}	t_scroll;

#endif