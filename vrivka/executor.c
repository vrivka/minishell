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
		{
			if (g_msh.pipe[0].l_fd < 0 || g_msh.pipe[0].r_fd < 0)
			{
				g_msh.ret = 1;
				return ;
			}
			dup2(g_msh.pipe[0].l_fd, 0);
			dup2(g_msh.pipe[0].r_fd, 1);
		}
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

int text_document(char *delim)
{
	int fd;
	char *s;

	fd = open("./.text_document", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		error_func(NULL, 1, 1, NULL);
	while (1)
	{
		s = readline("> ");
		if (!ft_strcmp(s, delim))
			break ;
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(s);
	}
	free(s);
	close(fd);
	fd = open("./.text_document", O_RDONLY);
	unlink("./.text_document");
	return (fd);
}

void open_redirs(char **rd, int n)
{
	int i;

	i = 0;
	while (rd[i])
	{
		if (!ft_strcmp(rd[i], "<"))
		{
			if (g_msh.pipe[n].l_fd > 2)
				close(g_msh.pipe[n].l_fd);
			g_msh.pipe[n].l_fd = open(rd[i + 1], O_RDONLY);
		}
		else if (!ft_strcmp(rd[i], "<<"))
		{
			if (g_msh.pipe[n].l_fd > 2)
				close(g_msh.pipe[n].l_fd);
			g_msh.pipe[n].l_fd = text_document(rd[i + 1]);
		}
		else if (!ft_strcmp(rd[i], ">"))
		{
			if (g_msh.pipe[n].r_fd > 2)
				close(g_msh.pipe[n].r_fd);
			g_msh.pipe[n].r_fd = open(rd[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (!ft_strcmp(rd[i], ">>"))
		{
			if (g_msh.pipe[n].r_fd > 2)
				close(g_msh.pipe[n].r_fd);
			g_msh.pipe[n].r_fd = open(rd[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		if (g_msh.pipe[n].l_fd < 0 || g_msh.pipe[n].r_fd < 0)
		{
			if (g_msh.pipe[n].r_fd > 2)
				close(g_msh.pipe[n].r_fd);
			if (g_msh.pipe[n].l_fd > 2)
				close(g_msh.pipe[n].l_fd);
			error_func(NULL, 1, 1, rd[i + 1]);
			break ;
		}
		i += 2;
	}
}

void redirs(void)
{
	int i;

	i = 0;
	printf("%d %d\n", g_msh.pipe[i].l_fd, g_msh.pipe[i].r_fd);
	while (i < g_msh.pipe_count)
	{
		g_msh.pipe[i].l_fd = 0;
		g_msh.pipe[i].r_fd = 1;
		open_redirs(g_msh.pipe[i].rd, i);
		i++;
	}
	printf("%d %d\n", g_msh.pipe[i].l_fd, g_msh.pipe[i].r_fd);
}

void close_redirs(void)
{
	int i;

	i = 0;
	while (i < g_msh.pipe_count)
	{
		if (g_msh.pipe[i].r_fd > 2)
			close(g_msh.pipe[i].r_fd);
		if (g_msh.pipe[i].l_fd > 2)
			close(g_msh.pipe[i].l_fd);
		i++;
	}
}

void executor(void)
{
	redirs();
	printf("%d %d\n", g_msh.pipe[0].l_fd, g_msh.pipe[0].r_fd);
	if (g_msh.pipe_count == 1)
		exec_without_pipes();
	else
		g_msh.ret = exec_pipes();
	close_redirs();
}
