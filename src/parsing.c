/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 12:54:38 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/08/07 13:53:13 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Returns the length of a string.
static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// Exits program with a selected error message written beforehand.
void	exit_error(char *error_message)
{
	if (write (1, error_message, ft_strlen(error_message)) == -1)
		exit(1);
	exit(1);
}

// Compares 2 strings with one another.
// Returns the difference in ascii if there is one.
static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (i < n)
	{
		if ((str1[i] == '\0') || (str2[i] == '\0') || (str1[i] != str2[i]))
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

static void	setup_julia(int argc, char **argv, t_root *root)
{
	if (argc == 3)
	{
		root->set = JULIA;
		root->r_julia.x = 0;
		root->r_julia.y = ft_atof(argv[argc - 1], CHECK_I);
	}
	else
	{
		root->set = JULIA;
		root->r_julia.x = ft_atof(argv[argc - 3], DONT_CHECK_I);
		root->r_julia.y = ft_atof(argv[argc - 1], CHECK_I)
			* ft_atosign(argv[argc - 2]);
	}
}

// Checks if the command line input is correct and selects the proper settings.
void	check_input(int argc, char **argv, t_root *root)
{
	root->width = 1920;
	root->height = 1080;
	if (argc == 2 && !(ft_strncmp(argv[1], "mandelbrot", 11)))
		root->set = MANDELBROT;
	else if (argc == 2 && !(ft_strncmp(argv[1], "vela", 5)))
		root->set = VELA;
	else if (argc == 2 && !(ft_strncmp(argv[1], "mouse", 6)))
	{
		root->height = 800;
		root->width = 800;
		root->set = MOUSE;
	}
	else if (argc == 2 && !(ft_strncmp(argv[1], "julia", 6)))
		exit_error("Use a valid constant\nTry 0.285 + 0.01i\nOr try 0.8i\n");
	else if (argc == 3 && !(ft_strncmp(argv[1], "julia", 6)))
		setup_julia(argc, argv, root);
	else if (argc == 5 && !(ft_strncmp(argv[1], "julia", 6)))
		setup_julia(argc, argv, root);
	else
		exit_error("Please use a valid argument:\nmandelbrot\njulia\nvela\nmouse\n");
}
