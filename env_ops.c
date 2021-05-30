#include "minishell.h"

//vlad
int		envncmp(const char *env, const char *find)
{
	int		i;

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

int		env_finder(char **env, char *name)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (envncmp(env[i], name))
			return (i);
		i++;
	}
	return (-1);
}

char	*env_val_cut(const char *env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (0);
	i++;
	tmp = ft_strdup(&env[i]);
	if (!tmp)
		error_func(ERROR_MEM, 1, 0, NULL);
	return (tmp);
}

char	*env_value(char **env, char *name)
{
	char	*tmp;
	int		i;

	i = env_finder(env, name);
	if (i == -1)
		return (0);
	tmp = env_val_cut(env[i]);
	return (tmp);
}
//vlad