#include "minishell.h"

void	swap_string(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort_env(char **exp)
{
	int	i;
	int	j;

	i = 0;
	while (exp[i])
	{
		j = i + 1;
		while (exp[j])
		{
			if (ft_strcmp(exp[i], exp[j]) > 0)
				swap_string(&exp[i], &exp[j]);
			j++;
		}
		i++;
	}
}

void	print_export(char **exp)
{
	int	a;
	int	i;
	int	j;

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

void	print_exp(void)
{
	char	**envc;

	envc = envcpy(g_msh.envp);
	if (!envc)
		error_func(ERROR_MEM, 1, 0, NULL);
	sort_env(envc);
	print_export(envc);
	free_envc(envc, envlen(envc));
}

int	export_func(char **av)
{
	int	i;
	int	r;

	r = 0;
	if (!av[1])
		print_exp();
	else
	{
		i = 1;
		while (av[i])
		{
			if (check_args(av[i]))
				r = 1;
			else
				export_arg(av[i]);
			i++;
		}
	}
	return (r);
}
