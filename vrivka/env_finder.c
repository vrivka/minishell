#include "minishell.h"

char *env_name_cut(const char *env)
{
	char *tmp;
	int i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		tmp[i] = env[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

char **env_add(char *av)
{
	char **tmp;
	int l;
	int i;

	l = envlen(g_msh.envp);
	tmp = (char **)malloc(sizeof(char *) * (l + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (g_msh.envp[i])
	{
		tmp[i] = ft_strdup(g_msh.envp[i]);
		if (!tmp[i])
			return (free_envc(tmp, i - 1));
		i++;
	}
	tmp[i] = ft_strdup(av);
	if (!tmp[i])
		return (free_envc(tmp, i - 1));
	tmp[i + 1] = 0;
	free_envc(g_msh.envp, l);
	return (tmp);
}

char **env_del(char *name)
{
	char **tmp;
	int l;
	int i;
	int n;
	int j;

	n = env_finder(g_msh.envp, name);
	l = envlen(g_msh.envp);
	tmp = (char **)malloc(sizeof(char *) * l);
	if (!tmp)
		return (0);
	i = 0;
	j = 0;
	while (g_msh.envp[i])
	{
		if (i != n)
		{
			tmp[j] = ft_strdup(g_msh.envp[i]);
			if (!tmp[j])
				return (free_envc(tmp, i - 1));
			j++;
		}
		i++;
	}
	tmp[j] = 0;
	free_envc(g_msh.envp, l);
	return (tmp);
}
