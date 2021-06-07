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

int exec_pipes(void)
{
	int i;
	int r;

	pipe_init();
	i = 0;
	while (i < g_msh.pipe_count)
	{
		if (i < g_msh.pipe_count - 1)
			pipe(g_msh.pipe_fd[i]);
		exec_pipe_func(g_msh.pipe[i].args, i);
		i++;
	}
	wait(&r);
	return (WEXITSTATUS(r));
}

void executor(void)
{
	printf("%d\n", g_msh.pipe_count);
	if (g_msh.pipe_count == 1)
		exec_without_pipes();
	else
		g_msh.ret = exec_pipes();
}

