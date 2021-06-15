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

int	text_document(char *delim)
{
	int		fd;
	char	*s;

	fd = open("./.text_document", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		error_func(NULL, 1, 1, NULL);
	while (1)
	{
		s = readline("> ");
		if (!ft_strcmp(s, delim))
			break ;
		s = parse_redir(s, g_msh.envp);
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
