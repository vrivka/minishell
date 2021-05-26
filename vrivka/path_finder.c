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
		return (NULL);
	tmp = ft_split(env_path, ':');
	if (!tmp) //error_func
		exit (1);
	tmp = slash_add(tmp);
	i = 0;
	while (tmp[i])
	{
		path = ft_strjoin(tmp[i], av_null);
		printf("%s\t%s\n", tmp[i], path);
		if (!path) //error_func
			exit (1);
		st = stat(path, &buf);
		if (!st)
			break ;
		free(path);
		i++;
	}
//	printf("%d\n", st);
	if (st)
		return (0);
	free_envc(tmp, envlen(tmp));
	free(env_path);
	return(path);
}

int exec_func(char **av)
{
	char *bin_path;
	int pid;
//	int fd;
	int r;

	bin_path = path_finder(env_value(g_msh.envc, "PATH"), g_msh.pars->args[0]);//g_msh.pars->args[0]
	if (!bin_path)
		printf("%s\n", strerror(errno));
	else
		printf("%s\n", bin_path);
	pid = fork();
	if (pid == 0)
	{
//		fd = open("./file", O_RDONLY);
//		r = dup2(fd, 0);
//		printf("%d\n", r);
		r = execve(bin_path, av, g_msh.envc);
		exit(r);
	}
	else
	{
		wait(&r);
	}
	free(bin_path);
	return (0);
}
