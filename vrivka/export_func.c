#include "minishell.h"

void swap_string(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
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
			if (strcmp(exp[i], exp[j]) > 0)
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
	int i;

	i = 0;
	while (g_msh.envc[i])
		i++;
	envc = (char **)malloc(sizeof(char *) * (i));
	if (!envc)
		return ;
	i = 0;
	while (g_msh.envc[i])
	{
		if (!strncmp(g_msh.envc[i], "_=", 2))
			i++;
		else
		{
			envc[i] = g_msh.envc[i];
			i++;
		}
	}
	envc[i] = 0;
	sort_env(envc);
	print_export(envc);
	free(envc);
}

void change_env(const char *env, int n)
{
	int i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return ;
	free(g_msh.envc[n]);
	g_msh.envc[n] = ft_strdup(env);
}

void exp_env_add(char *env)
{
	g_msh.envc = env_add(env);
	if (!g_msh.envc)
		exit (1);
}

void export_func(char **av)
{
	int i;
	int n;

	if (!av[1])
		print_exp();
	else
	{
		i = 1;
		while (av[i])
		{
			n = env_finder(g_msh.envc, av[i]);
			if (n >= 0)
				change_env(av[i], n);
			else
				exp_env_add(av[i]);
			i++;
		}
	}
}
