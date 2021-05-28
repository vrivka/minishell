#include "minishell.h"

char **slash_add(char **arr)
{
	char **tmp;
	int l;
	int i;

	l = envlen(arr);
	tmp = (char **)malloc(sizeof(char *) * (l + 1));
	if (!tmp) //error_func
		exit(1);
	i = 0;
	while (arr[i])
	{
		tmp[i] = ft_strjoin(arr[i], "/");
		if (!tmp[i])
			return (free_envc(tmp, i));
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

	if (!env_path)
		return (ft_strdup(av_null));
	tmp = ft_split(env_path, ':');
	if (!tmp) //error_func
		exit (1);
	tmp = slash_add(tmp);
	if (!tmp) //error_func
		exit (1);
	i = 0;
	while (tmp[i])
	{
		path = ft_strjoin(tmp[i], av_null);
		if (!path) //error_func
			exit (1);
		st = stat(path, &buf);
		if (!st)
			break ;
		free(path);
		i++;
	}
	if (st)
		return (ft_strdup(av_null));
	free_envc(tmp, envlen(tmp));
	free(env_path);
	return(path);
}

int exec_func(char **av)
{
	int pid;
	int r;

	pid = fork();
	if (pid == 0)
	{
		r = execve(g_msh.pars.bin_path, av, g_msh.envp);
		exit(r);
	}
	else
	{
		wait(&r);
	}
	return (0);
}
