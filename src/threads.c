/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 13:25:32 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/07 12:45:09 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	update_image(t_root *root)
{
	pthread_t	threadpool[THREADS];
	int			i;

	i = 0;
	root->y = 0;
	while (i < THREADS)
	{
		pthread_create(&threadpool[i], NULL, change_image, root);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threadpool[i], NULL);
		i++;
	}
	if (root->set == MOUSE)
		create_mandelbrot_picture(root);
}

void	init_mutexes(t_root *root)
{
	root->y = 0;
	if (pthread_mutex_init(&root->image_mutex, NULL) == -1)
		exit_error("Mutex creation error\n");
}
