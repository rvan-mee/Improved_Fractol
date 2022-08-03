#include <fractol.h>

void	create_threads(t_root *root)
{
	int	i;

	i = 0;
	root->threadpool = malloc(sizeof(pthread_t) * THREAD_COUNT);
	if (!root->threadpool)
		exit_error("Thread creation error\n");
	while (i < THREAD_COUNT)
	{
		pthread_create(root->threadpool[i], NULL, change_image, root);
		pthread_detach(root->threadpool[i]);
	}
}

void	init_mutexes(t_root *root)
{
	if (pthread_mutex_init(&root->image_mutex, NULL) == -1)
		exit_error("Mutex creation error\n");
}
