#include "minishell.h"

int env_func(void)
{
	int i;

	i = 0;
	while (g_msh.envp[i])
	{
		if (ft_strchr(g_msh.envp[i], '='))
			printf("%s\n", g_msh.envp[i]);
		i++;
	}
	return(0);
}
