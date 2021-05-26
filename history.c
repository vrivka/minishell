#include "minishell.h"

void	get_history(t_msh *msh, char **av)
{
	int		fd;
	char	*str;

	msh->hist_path = get_hist_path(av);
	fd = open(msh->hist_path, O_RDONLY | O_CREAT, 0666);//if fd = -1 error
	str = read_hist2str(fd);
	msh->history = get_hist_array(str);
	close(fd);
}

char	**get_hist_array(char *str)
{
	char	**arr;
	int		size;

	size = get_arr_size(str);//count \n
	arr = (char **)ft_calloc(sizeof(char *), (size + 1));// if ar==NULL
	fill_array(arr, str);
	free(str);
	// //
	// int j; //print history array
	// j = 0;
	// while (arr[j] != NULL)
	// {
	// 	printf("%s\n", arr[j]);
	// 	j++;
	// }
	// //
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
	return (size + 1);//+1 because last line without \n
}

char	*read_hist2str(int fd)
{
	char	*buf;
	char	*s;
	int		rd;

	buf = (char *)ft_calloc(sizeof(char), 2);//if buf==NULL
	s = (char *)ft_calloc(sizeof(char), 1);//if s==NULL
	while ((rd = read(fd, &buf[0], 1)))//if rd==-1
		s = ft_strjoin_fr(s, buf);
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
	i = 0;
	while (i < len)
	{
		path[i] = av[0][i];
		i++;
	}
	path = ft_strjoin_fr(path, HIST_F_NAME);
	return (path);
}

void	put_hist2file(t_msh *msh)
{
	int	fd;
	int	j;
	int	size;

	fd = open(msh->hist_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);//if fd=-1 error
	size = count_arr_lines(msh->history);
	j = 0;
	while (msh->history[j] != NULL)
	{
		write(fd, msh->history[j], ft_strlen(msh->history[j]));
		if (j < (size - 1))
			write(fd, "\n", 1);
		j++;
	}
	close(fd);
	free_d_arr(msh->history);
}

int		count_arr_lines(char **array)
{
	int	count;

	count = 0;
	while (array[count] != NULL)
		count++;
	return (count);
}

void	insert_nline2hist(t_msh *msh)
{
	char	**arr;
	int		size;
	int		j;

	size = count_arr_lines(msh->history);
	arr = (char **)ft_calloc(sizeof(char *), (size + 2));//+1 for new line
	j = 0;
	while (j < size)
	{
		arr[j] = (char *)ft_calloc(sizeof(char), 0);
		arr[j] = ft_strrewrite(arr[j], msh->history[j]);
		j++;
	}
	arr[j] = (char *)ft_calloc(sizeof(char), 0);
	arr[j] = ft_strrewrite(arr[j], msh->line);
	free_d_arr(msh->history);
	msh->history = arr;
}



//start of minishell - open file (O_RDONLY | O_CREAT, 0666)
//read file to array
//close fd
//while working - press enter(\n) / ctrl-d / exit - open (O_WRONLY | O_CREAT | O_TRUNC, 0666)
//write array to file
//close fd