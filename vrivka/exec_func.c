#include "minishell.h"

int exec_func(char **av)
{
	int exit_status;
	int r;

	g_msh.pid = fork();
	if (g_msh.pid == 0)
	{
		r = execve(g_msh.pars.bin_path, av, g_msh.envp);
		exit(r);
	}
	else
	{
		wait(&r);
		exit_status = WEXITSTATUS(r);
	}
	return (exit_status);
}
