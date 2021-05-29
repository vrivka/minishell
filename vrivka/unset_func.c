#include "minishell.h"

int unset_func(char **av)
{
	int i;
	int n;

	i = 1;
	if (!av[1])
		return (0);
	while (av[i])
	{
		if (check_args(av[i]))
			return (error_func("minishell: unset: %s: not a valid identifier\n", 1, 1, av[i]));
		n = env_finder(g_msh.envp, av[i]);
		if (n >= 0)
			g_msh.envp = env_del(av[i]);
		i++;
	}
	return (0);
}
