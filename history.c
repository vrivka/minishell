#include "minishell.h"

void	get_history(char **av)
{
	int		fd;
	char	*str;

	g_msh.hist_path = get_hist_path(av);
	fd = open(g_msh.hist_path, O_RDONLY | O_CREAT, 0666);
	if (fd == -1)
		error_func(ERR_OPCRHISF, 1, 0, NULL);
	str = read_hist2str(fd);
	g_msh.history = get_hist_array(str);
	close(fd);
}

char	**get_hist_array(char *str)
{
	char	**arr;
	int		size;

	size = get_arr_size(str);
	arr = (char **)ft_calloc(sizeof(char *), (size + 1));
	if (arr == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	fill_array(arr, str);
	free(str);
	return (arr);
}

void	fill_array(char **arr, char *str)
{
	int	i;
	int	j;
	int	n;
	int	len;

	n = 0;
	j = 0;
	while (str[n] != '\0')
	{
		len = get_str_len(str, n);
		arr[j] = (char *)ft_calloc(sizeof(char), (len + 1));
		if (arr[j] == NULL)
			error_func(ERROR_MEM, 1, 0, NULL);
		i = 0;
		while (str[n] != '\n' && str[n] != '\0')
		{
			arr[j][i] = str[n];
			i++;
			n++;
		}
		if (str[n] == '\0')
			break;
		else
		{
			n++;
			j++;
		}
	}
}

int		get_str_len(char *str, int n)
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

int		get_arr_size(char *str)
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
	return (size + 1);
}

char	*read_hist2str(int fd)
{
	char	*buf;
	char	*s;
	int		rd;

	buf = (char *)ft_calloc(sizeof(char), 2);
	if (buf == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	s = (char *)ft_calloc(sizeof(char), 1);
	if (s == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	while ((rd = read(fd, &buf[0], 1)))
	{
		if (rd == -1)
			error_func(ERR_READHISF, 1, 0, NULL);
		s = ft_strjoin_fr(s, buf);
	}
	free(buf);
	return (s);
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

void	put_hist2file(void)
{
	int	fd;
	int	j;
	int	size;

	fd = open(g_msh.hist_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		error_func(ERR_OPCRHISF, 1, 0, NULL);
	size = count_arr_lines(g_msh.history);
	j = 0;
	while (g_msh.history[j] != NULL)
	{
		write(fd, g_msh.history[j], ft_strlen(g_msh.history[j]));
		if (j < (size - 1))
			write(fd, "\n", 1);
		j++;
	}
	close(fd);
	free_d_arr(g_msh.history);
}

int		count_arr_lines(char **array)
{
	int	count;

	count = 0;
	while (array[count] != NULL)
		count++;
	return (count);
}
