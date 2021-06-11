#include "minishell.h"

void swap_string(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int my_strcmp(const char *s1, const char *s2) //заменить
{
	int i;
	int r;

	i = 0;
	while (s1[i])
	{
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (r)
			return (r);
		i++;
	}
	return (r);
}

void sort_env(char **exp)
{
	int i;
	int j;

	i = 0;
	while (exp[i])
	{
		j = i + 1;
		while (exp[j])
		{
			if (my_strcmp(exp[i], exp[j]) > 0) //заменить
				swap_string(&exp[i], &exp[j]);
			j++;
		}
		i++;
	}
}

void print_export(char **exp)
{
	int a;
	int i;
	int j;

	a = 0;
	while (exp[a])
	{
		i = 0;
		if (!ft_strncmp(exp[a], "_=", 2))
		{
			a++;
			continue ;
		}
		while (exp[a][i] != '=' && exp[a][i] != 0)
			i++;
		if (exp[a][i] == 0)
			printf("declare -x %s\n", exp[a]);
		else
		{
			j = i + 1;
			printf("declare -x %.*s=\"%s\"\n", i, exp[a], &exp[a][j]);
		}
		a++;
	}
}

void print_exp(void)
{
	char **envc;

	envc = envcpy(g_msh.envp);
	sort_env(envc);
	print_export(envc);
	free_envc(envc, envlen(envc));
}

void change_env(const char *env, int n)
{
	int i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return ;
	free(g_msh.envp[n]);
	g_msh.envp[n] = ft_strdup(env);
	if (!g_msh.envp[n])
		error_func(ERROR_MEM, 1, 0, NULL);
}

void exp_env_add(char *env)
{
	g_msh.envp = env_add(env);
	if (!g_msh.envp)
		error_func(ERROR_MEM, 1, 0, NULL);
}

int check_args(char *arg)
{
	if (ft_isalpha(arg[0]))
		return (0);
	return (1);
}

int export_func(char **av)
{
	int i;
	int n;
	int r;

	r = 0;
	if (!av[1])
		print_exp();
	else
	{
		i = 1;
		while (av[i])
		{
			if (check_args(av[i]))
				r = error_func("minishell: export: %s: not a valid identifier\n", 1, 1, av[i]);
			n = env_finder(g_msh.envp, av[i]);
			if (n >= 0)
				change_env(av[i], n);
			else
				exp_env_add(av[i]);
			i++;
		}
	}
	return (r);
}
