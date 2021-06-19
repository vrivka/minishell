#include "minishell.h"

void	pipe_init(void)
{
	int	i;

	if (g_msh.pipe_count > 1)
	{
		g_msh.pipe_fd = (int **) malloc(sizeof(int *) * (g_msh.pipe_count - 1));
		if (!g_msh.pipe_fd)
			error_func(ERROR_MEM, 1, 0, NULL);
		i = g_msh.pipe_count - 2;
		while (i >= 0)
		{
			g_msh.pipe_fd[i] = (int *) malloc(sizeof(int) * 2);
			if (!g_msh.pipe_fd[i])
				error_func(ERROR_MEM, 1, 0, NULL);
			i--;
		}
	}
	redirs();
}

void	close_redirs_free_pipes(void)
{
	int	i;

	i = 0;
	while (i < g_msh.pipe_count)
	{
		if (g_msh.pipe[i].r_fd > 2)
			close(g_msh.pipe[i].r_fd);
		if (g_msh.pipe[i].l_fd > 2)
			close(g_msh.pipe[i].l_fd);
		i++;
	}
	if (g_msh.pipe_count > 1)
	{
		i = 0;
		while (i < g_msh.pipe_count - 1)
		{
			free(g_msh.pipe_fd[i]);
			i++;
		}
		free(g_msh.pipe_fd);
	}
}

void	executor(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipe_init();
	if (g_msh.rdfl)
	{
		close_redirs_free_pipes();
		g_msh.rdfl = 0;
		return ;
	}
	if (g_msh.pipe_count == 1)
		g_msh.ret = exec_without_pipes();
	else
		g_msh.ret = exec_pipes();
	close_redirs_free_pipes();
}
