#include "minishell.h"

int	envlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**envcpy(char **env)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (envlen(env) + 1));
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
	tmp[i] = 0;
	return (tmp);
}
