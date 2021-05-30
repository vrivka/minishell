#include "minishell.h"

void executor(void)
{
	printf("%s\n", g_msh.pars.bin_path);
	if (!ft_strncmp(g_msh.pars.args[0], "echo", 5))
		g_msh.ret = echo_func(g_msh.pars.args);
	else if (!ft_strncmp(g_msh.pars.args[0], "cd", 3))
		g_msh.ret = cd_func(g_msh.pars.args);
	else if (!ft_strncmp(g_msh.pars.args[0], "pwd", 4))
		g_msh.ret = pwd_func();
	else if (!ft_strncmp(g_msh.pars.args[0], "export", 7))
		g_msh.ret = export_func(g_msh.pars.args);
	else if (!ft_strncmp(g_msh.pars.args[0], "unset", 6))
		g_msh.ret = unset_func(g_msh.pars.args);
	else if (!ft_strncmp(g_msh.pars.args[0], "env", 4))
		g_msh.ret = env_func();
	else if (!ft_strncmp(g_msh.pars.args[0], "exit", 5))
		g_msh.ret = exit_func(g_msh.pars.args);
	else
		g_msh.ret = exec_func(g_msh.pars.args);
}
