#include "minishell.h"

void exec_without_pipes(void)
{
	int r;
	int fd_1;
	int fd_0;

	r = it_builtin(0);
	if (r)
	{
		fd_0 = dup(0);
		fd_1 = dup(1);
		if (g_msh.pipe[0].rd)
			open_dup_redirs(g_msh.pipe[0].rd);
		g_msh.ret = exec_builtin(0, r);
		dup2(fd_0, 0);
		dup2(fd_1, 1);
		close(fd_0);
		close(fd_1);
	}
	else
		g_msh.ret = exec_func(g_msh.pipe[0].args);
}

void pipe_init(void)
{
	int i;

	g_msh.pipe_fd = (int **)malloc(sizeof(int *) * (g_msh.pipe_count - 1));
	if (!g_msh.pipe_fd)
		error_func(ERROR_MEM, 1, 0, NULL); // error_func
	i = g_msh.pipe_count - 2;
	while (i >= 0)
	{
		g_msh.pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!g_msh.pipe_fd[i])
			error_func(ERROR_MEM, 1, 0, NULL); //error_func
		i--;
	}
}

void free_pipe_fd(int **fd, int pipe_count)
{
	int i;

	i = 0;
	while (i < pipe_count - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int exec_pipes(void)
{
	int i;
	int r;

	pipe_init();
	if (pipe(g_msh.pipe_fd[0]) < 0)
		error_func(NULL, 1, 1, NULL);
	exec_pipe_func(g_msh.pipe[0].args, 0);
	i = 1;
	while (i < g_msh.pipe_count - 1)
	{
		if (pipe(g_msh.pipe_fd[i]) < 0)
			error_func(NULL, 1, 1, NULL);
		exec_pipe_func(g_msh.pipe[i].args, i);
		close(g_msh.pipe_fd[i - 1][0]);
		close(g_msh.pipe_fd[i - 1][1]);
		i++;
	}
	exec_pipe_func(g_msh.pipe[i].args, i);
	close(g_msh.pipe_fd[i - 1][0]);
	close(g_msh.pipe_fd[i - 1][1]);
	i = 0;
	while (i < g_msh.pipe_count)
	{
		waitpid(0, &r, 0);
		i++;
	}
	free_pipe_fd(g_msh.pipe_fd, g_msh.pipe_count);
	return (WEXITSTATUS(r));
}

void executor(void)
{
	if (g_msh.pipe_count == 1)
		exec_without_pipes();
	else
		g_msh.ret = exec_pipes();
}

