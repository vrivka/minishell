#include "minishell.h"

void open_dup_pipes(int i)
{
	if (i)
	{
		dup2(g_msh.pipe_fd[i - 1][0], 0);
		close(g_msh.pipe_fd[i - 1][0]);
		close(g_msh.pipe_fd[i - 1][1]);
	}
	if (i + 1 < g_msh.pipe_count)
	{
		dup2(g_msh.pipe_fd[i][1], 1);
		close(g_msh.pipe_fd[i][1]);
		close(g_msh.pipe_fd[i][0]);
	}
}

int it_builtin(int i)
{
	if (!ft_strncmp(g_msh.pipe[i].args[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "cd", 3))
		return (2);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "pwd", 4))
		return (3);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "export", 7))
		return (4);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "unset", 6))
		return (5);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "env", 4))
		return (6);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "exit", 5))
		return (7);
	else
		return (0);
}

int exec_builtin(int i, int n)
{
	int r;

	r = 0;
	if (n == 1)
		r = echo_func(g_msh.pipe[i].args);
	else if (n == 2)
		r = cd_func(g_msh.pipe[i].args);
	else if (n == 3)
		r = pwd_func();
	else if (n == 4)
		r = export_func(g_msh.pipe[i].args);
	else if (n == 5)
		r = unset_func(g_msh.pipe[i].args);
	else if (n == 6)
		r = env_func();
	else if (n == 7)
		r = exit_func(g_msh.pipe[i].args);
	return (r);
}

void exec_pipe_func(char **av, int i)
{
	int r;

	g_msh.pid = fork();
	if (g_msh.pid == 0)
	{
		if (g_msh.pipe_count > 1)
			open_dup_pipes(i);
		if (g_msh.pipe[i].rd)
			open_dup_redirs(g_msh.pipe[i].rd);
		r = it_builtin(i);
		if (r)
			r = exec_builtin(i, r);
		else
		{
			r = execve(g_msh.pipe[i].bin_path, av, g_msh.envp);
			if (r < 0)
				error_func(NULL, 1, 0, g_msh.pipe[i].bin_path);
		}
		close(g_msh.l_fd);
		close(g_msh.r_fd);
		exit(r);
	}
}

