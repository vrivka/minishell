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
	g_msh.envc = envcpy(env);
	export_func(tmp);
	g_msh.pwd = NULL;
	g_msh.pars = NULL;
	free_envc(tmp, 1);
}

void all_free(void)
{
	int i;

	i = 0;
	if (!g_msh.envc)
	{
		while (g_msh.envc[i])
		{
			free(g_msh.envc[i]);
			i++;
		}
		free(g_msh.envc);
	}
	if (!g_msh.pwd)
		free(g_msh.pwd);
}
