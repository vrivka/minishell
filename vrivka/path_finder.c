#include "minishell.h"

char **slash_add(char **arr)
{
	char **tmp;
	int l;
	int i;

	l = envlen(arr);
	tmp = (char **)malloc(sizeof(char *) * (l + 1));
	if (!tmp)
		error_func(ERROR_MEM, 1, 0, NULL);
	i = 0;
	while (arr[i])
	{
		tmp[i] = ft_strjoin(arr[i], "/");
		if (!tmp[i])
			error_func(ERROR_MEM, 1, 0, NULL);
		i++;
	}
	tmp[i] = 0;
	free_envc(arr, l);
	return (tmp);
}

char *path_finder(char *env_path, char *av_null)
{
	char *path;
	char **tmp;
	struct stat buf;
	int st;
	int i;

	if (!strncmp(av_null, "/", 1) || !strncmp(av_null, "./", 2) || !strncmp(av_null, "../", 3) || !env_path)
	{
		path = ft_strdup(av_null);
		return (path);
	}
	tmp = ft_split(env_path, ':');
	if (!tmp)
		error_func(ERROR_MEM, 1, 0, NULL);
	tmp = slash_add(tmp);
	i = 0;
	while (tmp[i])
	{
		path = ft_strjoin(tmp[i], av_null);
		if (!path)
			error_func(ERROR_MEM, 1, 0, NULL);
		st = stat(path, &buf);
		if (!st)
			break ;
		free(path);
		i++;
	}
	if (st)
		path = ft_strdup(av_null);
	free_envc(tmp, envlen(tmp));
	free(env_path);
	return(path);
}
