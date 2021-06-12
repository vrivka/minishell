#include "minishell.h"

void	change_env(const char *env, int n)
{
	int	i;

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

void	exp_env_add(char *env)
{
	g_msh.envp = env_add(g_msh.envp, env, envlen(g_msh.envp));
	if (!g_msh.envp)
		error_func(ERROR_MEM, 1, 0, NULL);
}

int	check_args(char *arg)
{
	if (ft_isalpha(arg[0]))
		return (0);
	return (error_func("minishell: export: %s: not a valid identifier\n",
			1, 1, arg));
}

void	export_arg(char *arg)
{
	int	n;

	n = env_finder(g_msh.envp, arg);
	if (n >= 0)
		change_env(arg, n);
	else
		exp_env_add(arg);
}
