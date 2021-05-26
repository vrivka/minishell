#include "minishell.h"

char **cd_pwd(char *pwd)
{
	char **tmp;

	tmp = ft_split("export PWD OLDPWD", ' ');
	if (!tmp) //error_func
		error_func("ERRMEM", 1, 0, NULL);
	free(tmp[1]);
	tmp[1] = ft_strdup(pwd);
	return (tmp);
}

int cd_home(void)
{
	char **arr;
	int i;

	i = env_finder(g_msh.envc, "HOME");
	if (i == -1) //error_func
		return(error_func("minishell: cd: HOME not set", 1, 1, ""));
	arr = ft_split("cd a", ' ');
	if (!arr) //error_func
		error_func("minishell: Cannot allocate memory", 1, 0, "");
	free(arr[1]);
	arr[1] = env_value(g_msh.envc, "HOME");
	cd_func(arr);
	free_envc(arr, 1);
	return (0);
}

int cd_func(char **av)
{
	int code;
	char **pwd;
	char *tmp;

	if (!av[1])
		return (cd_home());
	tmp = getcwd(NULL, 0);
	pwd = cd_pwd(ft_strjoin("OLDPWD=", tmp));
	free(tmp);
	code = chdir(av[1]);
	if (code == -1) //error_func
		return (error_func(NULL, 1, 1, av[1]));
	free(pwd[2]);
	tmp = getcwd(NULL, 0);
	pwd[2] = ft_strjoin("PWD=", tmp);
	export_func(pwd);
	free(tmp);
	free_envc(pwd, 2);
	return (0);
}
