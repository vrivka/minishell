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

char	*check_bs(char *nl, const char *ol, int *i)
{
	if (ol[*i + 1] == '\\')
	{
		nl = augment_char(nl, '\\');
		*i += 1;
	}
	else if (ol[*i + 1] == '$')
	{
		nl = augment_char(nl, '$');
		*i += 1;
	}
	else
		nl = augment_char(nl, '\\');
	return (nl);
}

char	*val_ret(char *ol, char **env, int *i)
{
	char	*env_val;
	char	*env_name;

	env_name = NULL;
	while (ol[*i + 1] && (ft_isalnum(ol[*i + 1]) || ol[*i + 1] == '_'))
	{
		env_name = augment_char(env_name, ol[*i + 1]);
		*i += 1;
	}
	env_val = env_value(env, env_name);
	free(env_name);
	return (env_val);
}

char	*check_dol(char *nl, char *ol, int *i, char **env)
{
	char	*env_val;
	int		j;

	if (ol[*i + 1] == '?')
	{
		env_val = ft_itoa(g_msh.ret);
		if (!env_val)
			error_func(ERROR_MEM, 1, 0, NULL);
		*i += 1;
	}
	else if (!ol[*i + 1] || (!ft_isalnum(ol[*i + 1]) && ol[*i + 1] != '_'))
		return (augment_char(nl, '$'));
	else
		env_val = val_ret(ol, env, i);
	if (env_val)
	{
		j = 0;
		while (env_val[j])
		{
			nl = augment_char(nl, env_val[j]);
			j++;
		}
		free(env_val);
	}
	return (nl);
}
