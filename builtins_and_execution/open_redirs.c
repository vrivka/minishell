#include "minishell.h"

void	redirs(void)
{
	int	i;

	i = 0;
	while (i < g_msh.pipe_count)
	{
		g_msh.pipe[i].l_fd = 0;
		g_msh.pipe[i].r_fd = 1;
		open_redirs(g_msh.pipe[i].rd, i);
		i++;
	}
}

char	*parse_redir(char *line, char **env)
{
	char	*new_line;
	int		i;

	if (check_line(line))
		return (line);
	new_line = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] != '\\' && line[i] != '$')
			new_line = augment_char(new_line, line[i]);
		else if (line[i] == '\\')
			new_line = check_bs(new_line, line, &i);
		else if (line[i] == '$')
			new_line = check_dol(new_line, line, &i, env);
		i++;
	}
	if (!new_line)
	{
		new_line = ft_strdup("");
		if (!new_line)
			error_func(ERROR_MEM, 1, 0, NULL);
	}
	free(line);
	return (new_line);
}

int	main_loop_rd(int fd, char *delim)
{
	g_msh.pos = 0;
	unset_term_rd();
	write(1, "> ", 2);
	tputs(save_cursor, 1, ft_putchar);
	if (!key_loop_rd())
		return (0);
	write(1, "\n", 1);
	set_term_rd();
	if (!ft_strcmp(g_msh.line, delim))
		return (0);
	g_msh.line = parse_redir(g_msh.line, g_msh.envp);
	write(fd, g_msh.line, ft_strlen(g_msh.line));
	write(fd, "\n", 1);
	g_msh.line = ft_strrewrite(g_msh.line, "");
	return (1);
}

int	text_document(char *delim)
{
	int		fd;

	fd = open("./.text_document", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		error_func(NULL, 1, 1, NULL);
	g_msh.line = ft_strnew(0);
	while (1)
	{
		if (!main_loop_rd(fd, delim))
			break ;
		else
			continue ;
	}
	set_term_rd();
	free(g_msh.line);
	close(fd);
	fd = open("./.text_document", O_RDONLY);
	unlink("./.text_document");
	return (fd);
}

void	open_redirs(char **rd, int n)
{
	int	i;

	i = 0;
	while (rd[i])
	{
		if (!ft_strcmp(rd[i], "<"))
			open_left_redir(rd[i + 1], n);
		else if (!ft_strcmp(rd[i], "<<"))
			open_double_left_redir(rd[i + 1], n);
		else if (!ft_strcmp(rd[i], ">"))
			open_right_redir(rd[i + 1], n);
		else if (!ft_strcmp(rd[i], ">>"))
			open_double_right_redir(rd[i + 1], n);
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
