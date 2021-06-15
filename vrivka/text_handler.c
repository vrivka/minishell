#include "minishell.h"

int	check_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' || line[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

char	*augment_char(char *line, char c)
{
	char	*tmp;
	int		i;

	if (!line)
		i = 0;
	else
		i = ft_strlen(line);
	tmp = (char *)malloc(sizeof(char) * (i + 2));
	if (!tmp)
		error_func(ERROR_MEM, 1, 0, NULL);
	if (line)
		ft_strlcpy(tmp, line, i + 1);
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(line);
	return (tmp);
}

char	*check_bs(char *line, const char *ptr_bs, int *i)
{
	if (ptr_bs[*i + 1] == '\\')
	{
		line = augment_char(line, '\\');
		*i += 1;
	}
	else if (ptr_bs[*i + 1] == '$')
	{
		line = augment_char(line, '$');
		*i += 1;
	}
	else
		line = augment_char(line, '\\');
	return (line);
}

char	*val_ret(char *ptr_dol, char **env, int *i)
{
	char	*env_val;
	char	*env_name;

	env_name = NULL;
	while (ptr_dol[*i + 1] && ft_isalnum(ptr_dol[*i + 1]))
	{
		env_name = augment_char(env_name, ptr_dol[*i + 1]);
		*i += 1;
	}
	env_val = env_value(env, env_name);
	free(env_name);
	return (env_val);
}

char	*check_dol(char *line, char *ptr_dol, int *i, char **env)
{
	char	*env_val;
	int		j;

	if (ptr_dol[*i + 1] == '?')
	{
		env_val = ft_itoa(g_msh.ret);
		if (!env_val)
			error_func(ERROR_MEM, 1, 0, NULL);
		*i += 1;
	}
	else if (!ptr_dol[*i + 1] || !ft_isalnum(ptr_dol[*i + 1]))
		return (augment_char(line, '$'));
	else
		env_val = val_ret(ptr_dol, env, i);
	if (env_val)
	{
		j = 0;
		while (env_val[j])
		{
			line = augment_char(line, env_val[j]);
			j++;
		}
		free(env_val);
	}
	return (line);
}
