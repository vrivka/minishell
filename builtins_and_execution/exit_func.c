#include "minishell.h"

int	check_av(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int	exit_func(char **av)
{
	int	r;
	int	i;

	if (!av[1])
	{
		put_hist2file();
		write(1, "exit\n", 5);
		exit(0);
	}
	i = 0;
	while (av[i])
		i++;
	if (check_av(av[1]))
		error_func("exit\nminishell: exit: %s: numeric argument required\n",
			 255, 0, av[1]);
	if (i > 2)
		return (error_func("minishell: exit: too many arguments", 1, 1, NULL));
	r = ft_atoi(av[1]);
	put_hist2file();
	free(g_msh.term);
	write(1, "exit\n", 5);
	exit(r);
}
