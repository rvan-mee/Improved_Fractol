#include "fractol.h"

// Takes a string and checks if it is either a + or a - and will
// return 1, -1 or an error.
long double	ft_atosign(char *sign)
{
	int	i;

	i = 0;
	if (!sign)
		exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
	while (sign[i] != '\0')
		i++;
	if (i != 1)
		exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
	if (sign[0] == '+')
		return (1);
	else if (sign[0] == '-')
		return (-1);
	exit_error("Please use a valid constant\nTry this: 0.285 + 0.01i\n");
	return (0);
}