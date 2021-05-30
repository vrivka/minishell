#include "minishell.h"

int exit_func(char **av)
{
	int r;
	int i;

	if (!av[1])
		exit(0);
	i = 0;
	while (av[i])
		i++;
	if (i > 2)
		return (error_func("bash: exit: too many arguments", 1, 1, NULL));
	r = ft_atoi(av[1]);
	exit(r);
}
