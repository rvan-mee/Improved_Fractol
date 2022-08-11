/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 15:01:47 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/11 15:07:37 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSV_H
# define HSV_H

typedef struct s_hsv {
	float	h_increase;
	float	h_priem;
	float	r;
	float	g;
	float	b;
	float	h;
	float	s;
	float	v;	
	float	c;
	float	m;
	float	x;
	float	r1;
	float	g1;
	float	b1;
	float	x_min;
	float	x_max;
}	t_hsv;

#endif