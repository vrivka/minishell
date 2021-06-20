#include "minishell.h"

int	check_args_unset(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (error_func("minishell: unset: %s: not a valid identifier\n", \
							1, 1, arg));
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (error_func("minishell: unset: %s: not a valid identifier\n", \
								1, 1, arg));
		i++;
	}
	return (0);
}

int	unset_func(char **av)
{
	int	i;
	int	n;
	int	r;

	i = 1;
	r = 0;
	if (!av[1])
		return (0);
	while (av[i])
	{
		if (check_args_unset(av[i]))
			r = 1;
		n = env_finder(g_msh.envp, av[i]);
		if (n >= 0)
		{
			g_msh.envp = env_del(g_msh.envp, av[i], envlen(g_msh.envp));
			if (!g_msh.envp)
				error_func(ERROR_MEM, 1, 0, NULL);
		}
		i++;
	}
	return (r);
}
