#include "minishell.h"

int	get_str_len(char *str, int n)
{
	int	len;

	len = 0;
	while (str[n] != '\n' && str[n] != '\0')
	{
		len++;
		n++;
	}
	return (len);
}

int	get_arr_size(char *str)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			size++;
		i++;
	}
	return (size);
}

char	*get_hist_path(char **av)
{
	char	*path;
	int		len;
	int		i;

	len = ft_strlen(av[0]) - ft_strlen(EXEC_F_NAME);
	path = (char *)ft_calloc(sizeof(char), (len + 1));
	if (path == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	i = 0;
	while (i < len)
	{
		path[i] = av[0][i];
		i++;
	}
	path = ft_strjoin_fr(path, HIST_F_NAME);
	return (path);
}
