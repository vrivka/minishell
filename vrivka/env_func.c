#include "minishell.h"

int env_func(void)
{
	int i;

	i = 0;
	while (g_msh.envc[i])
	{
		if (ft_strchr(g_msh.envc[i], '='))
			printf("%s\n", g_msh.envc[i]);
		i++;
	}
	return(0);
}
