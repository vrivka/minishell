#include "minishell.h"

char **free_envc(char **envc, int i)
{
	while (i >= 0)
	{
		free(envc[i]);
		i--;
	}
	free(envc);
	return (NULL);
}

void all_init(char **env)
{
	char **tmp;

	tmp = ft_split("export OLDPWD", ' ');
	g_msh.envp = envcpy(env);
	export_func(tmp);
	g_msh.pwd = NULL;
	free_envc(tmp, 1);
}

void all_free(void)
{
	int i;

	i = 0;
	if (!g_msh.envp)
	{
		while (g_msh.envp[i])
		{
			free(g_msh.envp[i]);
			i++;
		}
		free(g_msh.envp);
	}
	if (!g_msh.pwd)
		free(g_msh.pwd);
}
