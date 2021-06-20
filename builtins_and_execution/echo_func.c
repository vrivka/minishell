#include "minishell.h"

int	echo_func(char **av)
{
	int	i;
	int	c;

	i = 1;
	c = 0;
	if (!av[i])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ft_strncmp(av[i], "-n\0", 3))
	{
		c = 1;
		i++;
	}
	while (av[i + 1])
	{
		write(1, av[i], ft_strlen(av[i]));
		write(1, " ", 1);
		i++;
	}
	write(1, av[i], ft_strlen(av[i]));
	if (c != 1)
		write(1, "\n", 1);
	return (0);
}
