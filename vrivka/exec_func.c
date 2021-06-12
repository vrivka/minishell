#include "minishell.h"

int exec_func(char **av)
{
	int r;

	g_msh.pid = fork();
	if (g_msh.pid == 0)
	{
		if (g_msh.pipe[0].rd)
		{
			if (g_msh.pipe[0].l_fd < 0 || g_msh.pipe[0].r_fd < 0)
				exit (1);
			dup2(g_msh.pipe[0].l_fd, 0);
			dup2(g_msh.pipe[0].r_fd, 1);
		}
		r = execve(g_msh.pipe[0].bin_path, av, g_msh.envp);
		if (r < 0)
			error_func(NULL, 1, 0, g_msh.pipe[0].bin_path);
		close(g_msh.pipe[0].l_fd);
		close(g_msh.pipe[0].r_fd);
		exit(r);
	}
	waitpid(0, &r, 0);
	return (WEXITSTATUS(r));
}
