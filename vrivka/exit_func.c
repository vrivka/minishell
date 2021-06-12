#include "minishell.h"

int	exit_func(char **av)
{
	int	r;
	int	i;

	if (!av[1])
	{
		put_hist2file();
		exit(0);
	}
	i = 0;
	while (av[i])
		i++;
	if (i > 2)
		return (error_func("minishell: exit: too many arguments", 1, 1, NULL));
	r = ft_atoi(av[1]);
	put_hist2file();
	exit(r);
}
