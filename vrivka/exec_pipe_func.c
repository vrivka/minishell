#include "minishell.h"

void	exec_pipe_func(char **av, int i)
{
	int	r;

	g_msh.pid = fork();
	if (g_msh.pid < 0)
		error_func(NULL, 1, 0, NULL);
	if (g_msh.pid == 0)
	{
		if (g_msh.pipe_count > 1)
			open_dup_pipes(i);
		if (g_msh.pipe[i].rd)
			close_if(g_msh.pipe[i].l_fd, g_msh.pipe[i].r_fd);
		r = it_builtin(i);
		if (r)
			r = exec_builtin(i, r);
		else
		{
			r = execve(g_msh.pipe[i].bin_path, av, g_msh.envp);
			if (r < 0)
				check_dir(g_msh.pipe[i].bin_path, 0);
		}
		exit(r);
	}
}

int	wait_all(int pipe_count)
{
	int	i;
	int	r;

	i = 0;
	while (i < pipe_count)
	{
		waitpid(0, &r, 0);
		i++;
	}
	return (r);
}

int	exec_pipes(void)
{
	int	i;
	int	r;

	if (pipe(g_msh.pipe_fd[0]) < 0)
		error_func(NULL, 1, 0, NULL);
	exec_pipe_func(g_msh.pipe[0].args, 0);
	i = 1;
	while (i < g_msh.pipe_count - 1)
	{
		if (pipe(g_msh.pipe_fd[i]) < 0)
			error_func(NULL, 1, 0, NULL);
		exec_pipe_func(g_msh.pipe[i].args, i);
		close(g_msh.pipe_fd[i - 1][0]);
		close(g_msh.pipe_fd[i - 1][1]);
		i++;
	}
	exec_pipe_func(g_msh.pipe[i].args, i);
	close(g_msh.pipe_fd[i - 1][0]);
	close(g_msh.pipe_fd[i - 1][1]);
	r = wait_all(g_msh.pipe_count);
	return (WEXITSTATUS(r));
}
