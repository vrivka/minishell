#include "minishell.h"

char *ft_strcjoin(char *s1, int c, char *s2)
{
	char *tmp;
	int i;

	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	i = ft_strlen(s1);
	ft_strlcpy(tmp, s1, i + 1);
	tmp[i] = (char)c;
	ft_strlcpy(&tmp[i + 1], s2, ft_strlen(s2) + 1);
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
	i = 0;
	while (tmp[i])
	{
		path = ft_strcjoin(tmp[i], '/', av_null);
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
