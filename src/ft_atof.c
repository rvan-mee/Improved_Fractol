#include "fractol.h"

// Created to avoid norm errors, would make the check_input_atof
// function have too many lines in it.
static int	atof_check_helper(char *s, int i)
{
	if ((s[i] == 'i' && s[i + 1] != '\0') || (s[i] == '.' && i == 0)
		|| (s[i] == '.' && !(s[i - 1] >= '0' && s[i - 1] <= '9'))
		|| (s[i] == '.' && s[i - 1] == 'i')
		|| (s[i] == '.' && s[i + 1] == '\0')
		|| (s[i] == '.' && s[i + 1] == 'i')
		|| (s[i] == 'i' && s[i + 1] == '\0' && i == 0))
		return (1);
	return (0);
}

// Checks if the input for atof is correct.
// Returns an error with exit_error if it fails the checks.
// Can check for imaginary numbers if specified.
static void	check_input_atof(char *s, int i_check)
{
	int		i;
	int		passed_dot;
	int		passed_i;

	i = 0;
	passed_dot = 0;
	passed_i = 0;
	if (s[0] == '-')
		i++;
	while ((s[i] != '\0' && (s[i] >= '0' && s[i] <= '9'))
		|| (s[i] != '\0' && s[i] == 'i') || (s[i] != '\0' && s[i] == '.'))
	{	
		if (atof_check_helper(s, i))
			exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
		if (s[i] == '.')
			passed_dot++;
		if (s[i] == 'i')
			passed_i++;
		i++;
	}
	if (s[i] != '\0' || passed_i != i_check || passed_dot > 1)
		exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
}

// Helper fuction of atof, sets all the converted chars in front of the decimal
// point and counts how many numbers should be past it.
static void	set_nbr_atof(int i, int *passed_dot, long double *nbr, char *str)
{
	while (str[i] != '\0')
	{
		if (str[i] == '.')
		{
			(*passed_dot)++;
			i++;
		}
		if (*passed_dot != 0 && !(str[i] == 'i'))
			(*passed_dot)++;
		if (!(str[i] == 'i'))
		{
			*nbr *= 10;
			*nbr += str[i] - '0';
		}
		i++;
	}
}

// Takes a string and converts it into a long double.
long double	ft_atof(char *str, int i_check)
{
	int			i;
	int			passed_dot;
	long double	sign;
	long double	nbr;

	check_input_atof(str, i_check);
	i = 0;
	nbr = 0;
	sign = 1;
	passed_dot = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	set_nbr_atof(i, &passed_dot, &nbr, str);
	while (passed_dot > 1)
	{
		nbr /= 10;
		passed_dot--;
	}
	return (nbr * sign);
}
