#include "minishell.h"

void	open_left_redir(char *path, int n)
{
	if (g_msh.pipe[n].l_fd > 2)
		close(g_msh.pipe[n].l_fd);
	g_msh.pipe[n].l_fd = open(path, O_RDONLY);
}

void	open_double_left_redir(char *path, int n)
{
	if (g_msh.pipe[n].l_fd > 2)
		close(g_msh.pipe[n].l_fd);
	g_msh.pipe[n].l_fd = text_document(path);
}

void	open_right_redir(char *path, int n)
{
	if (g_msh.pipe[n].r_fd > 2)
		close(g_msh.pipe[n].r_fd);
	g_msh.pipe[n].r_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

void	open_double_right_redir(char *path, int n)
{
	if (g_msh.pipe[n].r_fd > 2)
		close(g_msh.pipe[n].r_fd);
	g_msh.pipe[n].r_fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
}
