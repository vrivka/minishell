#include "minishell.h"

int envncmp(const char *env, const char *find)
{
	int i;

	i = 0;
	while (env[i] && env[i] != '=')
	{
		if (env[i] != find[i])
			return (0);
		i++;
	}
	if ((!env[i] || env[i] == '=') && (!find[i] || find[i] == '='))
		return (1);
	return (0);
}

int env_finder(char **env, char *name)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (envncmp(env[i], name))
			return (i);
		i++;
	}
	return (-1);
}

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

char *env_val_cut(const char *env)
{
	char *tmp;
	int i;
	int j;
	int k;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (0);
	i++;
	k = i;
	j = 0;
	while (env[i])
	{
		j++;
		i++;
	}
	tmp = (char *)malloc(sizeof(char) * (j + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (env[k])
	{
		tmp[i] = env[k];
		i++;
		k++;
	}
	tmp[i] = 0;
	return (tmp);
}

char *env_value(char **env, char *name)
{
	char *tmp;
	int i;

	i = env_finder(env, name);
	if (i == -1)
		return (0);
	tmp = env_val_cut(env[i]);
	return (tmp);
}

char **env_add(char *av)
{
	char **tmp;
	int l;
	int i;

	l = envlen(g_msh.envc);
	tmp = (char **)malloc(sizeof(char *) * (l + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (g_msh.envc[i])
	{
		tmp[i] = ft_strdup(g_msh.envc[i]);
		if (!tmp[i])
			return (free_envc(tmp, i - 1));
		i++;
	}
	tmp[i] = ft_strdup(av);
	if (!tmp[i])
		return (free_envc(tmp, i - 1));
	tmp[i + 1] = 0;
	free_envc(g_msh.envc, l);
	return (tmp);
}

char **env_del(char *name)
{
	char **tmp;
	int l;
	int i;
	int n;
	int j;

	n = env_finder(g_msh.envc, name);
	l = envlen(g_msh.envc);
	tmp = (char **)malloc(sizeof(char *) * l);
	if (!tmp)
		return (0);
	i = 0;
	j = 0;
	while (g_msh.envc[i])
	{
		if (i != n)
		{
			tmp[j] = ft_strdup(g_msh.envc[i]);
			if (!tmp[j])
				return (free_envc(tmp, i - 1));
			j++;
		}
		i++;
	}
	tmp[j] = 0;
	free_envc(g_msh.envc, l);
	return (tmp);
}
