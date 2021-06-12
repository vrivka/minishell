#include "minishell.h"

int	exec_without_pipes(void)
{
	int	r;
	int	fd_1;
	int	fd_0;

	r = it_builtin(0);
	if (r)
	{
		fd_0 = dup(0);
		fd_1 = dup(1);
		if (g_msh.pipe[0].rd)
		{
			if (g_msh.pipe[0].l_fd < 0 || g_msh.pipe[0].r_fd < 0)
				return (1);
			dup2(g_msh.pipe[0].l_fd, 0);
			dup2(g_msh.pipe[0].r_fd, 1);
		}
		r = exec_builtin(0, r);
		dup2(fd_0, 0);
		dup2(fd_1, 1);
		close(fd_0);
		close(fd_1);
	}
	else
		r = exec_func(g_msh.pipe[0].args);
	return (r);
}

int	exec_func(char **av)
{
	int	r;

	g_msh.pid = fork();
	if (g_msh.pid < 0)
		error_func(NULL, 1, 0, NULL);
	else if (g_msh.pid == 0)
	{
		if (g_msh.pipe[0].rd)
			close_if(g_msh.pipe[0].l_fd, g_msh.pipe[0].r_fd);
		r = execve(g_msh.pipe[0].bin_path, av, g_msh.envp);
		if (r < 0)
			error_func("minishell: %s: command not found\n",
				127, 0, g_msh.pipe[0].bin_path);
		close(g_msh.pipe[0].l_fd);
		close(g_msh.pipe[0].r_fd);
		exit(r);
	}
	waitpid(0, &r, 0);
	return (WEXITSTATUS(r));
}
