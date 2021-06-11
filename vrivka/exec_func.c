#include "minishell.h"

int text_document(char *delim)
{
	int fd;
	char *s;

	fd = open("./.text_document", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (1)
	{
		s = readline("> ");
		if (!ft_strcmp(s, delim))
			break ;
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(s);
	}
	close(fd);
	fd = open("./.text_document", O_RDONLY);
	return (fd);
}

void open_dup_redirs(char **rd)
{
	int i;

	i = 0;
	g_msh.l_fd = 0;
	g_msh.r_fd = 1;
	while (rd[i])
	{
		if (!ft_strcmp(rd[i], "<"))
			g_msh.l_fd = open(rd[i + 1], O_RDONLY);
		else if (!ft_strcmp(rd[i], "<<"))
			g_msh.l_fd = text_document(rd[i + 1]);
		else if (!ft_strcmp(rd[i], ">"))
			g_msh.r_fd = open(rd[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (!ft_strcmp(rd[i], ">>"))
			g_msh.r_fd = open(rd[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (g_msh.l_fd < 0 || g_msh.r_fd < 0)
			error_func(NULL, 1, 0, rd[i + 1]);
		i += 2;
	}
	dup2(g_msh.l_fd, 0);
	dup2(g_msh.r_fd, 1);
}


int exec_func(char **av)
{
	int r;

	g_msh.pid = fork();
	if (g_msh.pid == 0)
	{
		if (g_msh.pipe[0].rd)
			open_dup_redirs(g_msh.pipe[0].rd);
		r = execve(g_msh.pipe[0].bin_path, av, g_msh.envp);
		if (r < 0)
			error_func(NULL, 1, 0, g_msh.pipe[0].bin_path);
		close(g_msh.l_fd);
		close(g_msh.r_fd);
		unlink("./.text_document");
		exit(r);
	}
	waitpid(g_msh.pid, &r, 0);
	return (WEXITSTATUS(r));
}
