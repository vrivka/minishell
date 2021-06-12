#include "minishell.h"

char	**free_envc(char **envc, int i)
{
	while (i >= 0)
	{
		free(envc[i]);
		i--;
	}
	free(envc);
	return (NULL);
}

int	shlvl(void)
{
	char	*tmp;
	int		i;

	tmp = env_value(g_msh.envp, "SHLVL");
	if (!tmp)
		return (1);
	i = ft_atoi(tmp) + 1;
	free(tmp);
	return (i);
}
