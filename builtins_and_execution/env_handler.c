#include "minishell.h"

char	**env_add(char **env, char *av, int l)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (l + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		if (!tmp[i])
			return (free_envc(tmp, i - 1));
		i++;
	}
	tmp[i] = ft_strdup(av);
	if (!tmp[i])
		return (free_envc(tmp, i - 1));
	tmp[i + 1] = 0;
	free_envc(env, l);
	return (tmp);
}

char	**env_del(char **env, char *name, int l)
{
	char	**tmp;
	int		n;
	int		i;
	int		j;

	n = env_finder(env, name);
	tmp = (char **)malloc(sizeof(char *) * l);
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != n)
		{
			tmp[j] = ft_strdup(env[i]);
			if (!tmp[j])
				return (free_envc(tmp, i - 1));
			j++;
		}
		i++;
	}
	tmp[j] = 0;
	free_envc(env, l);
	return (tmp);
}
