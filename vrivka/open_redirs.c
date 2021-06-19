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

void	unset_term_rd(void)
{
	int	ret;

	g_msh.term->c_lflag &= ~(ECHO);
	g_msh.term->c_lflag &= ~(ICANON);

	g_msh.term->c_lflag &= ~(ISIG);

	ret = tcsetattr(0, TCSANOW, g_msh.term);
	if (ret == -1)
		error_func(ERR_SETTERM, 1, 0, NULL);
}

void	set_term_rd(void)
{
	int	ret;

	g_msh.term->c_lflag |= ECHO;
	g_msh.term->c_lflag |= ICANON;

	g_msh.term->c_lflag |= ISIG;

	ret = tcsetattr(0, TCSANOW, g_msh.term);
	if (ret == -1)
		error_func(ERR_SETTERM, 1, 0, NULL);
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
		g_msh.pos = 0;
		unset_term_rd();
		write(1, "> ", 2);
		tputs(save_cursor, 1, ft_putchar);
		if (!key_loop_rd())
		{
			set_term_rd();
			break;
		}
		write(1, "\n", 1);
		set_term_rd();

		if (!ft_strcmp(g_msh.line, delim))
			break ;
		g_msh.line = parse_redir(g_msh.line, g_msh.envp);
		write(fd, g_msh.line, ft_strlen(g_msh.line));
		write(fd, "\n", 1);
		g_msh.line = ft_strrewrite(g_msh.line,"");
	}
	free(g_msh.line);
	close(fd);
	fd = open("./.text_document", O_RDONLY);
	unlink("./.text_document");
	return (fd);
}

int	key_loop_rd(void)
{
	char	buf[BUFFER_SIZE];
	int		len;

	g_msh.rdfl = 0;
	wait4signal_rd();
	while (1)
	{
		ft_memset(buf, 0, BUFFER_SIZE);
		len = read(0, buf, BUFFER_SIZE);
		if (len == -1)
			error_func(ERR_READKEY, 1, 0, NULL);
		else if (!ft_strcmp(buf, "\e[D"))//left
		{
			if (g_msh.pos > 0)
			{
				tputs(tgetstr("le", 0), 1, ft_putchar);
				g_msh.pos--;
			}
		}
		else if (!ft_strcmp(buf, "\e[C"))//right
		{
			if (g_msh.pos < ft_strlen(g_msh.line))
			{
				tputs(tgetstr("nd", 0), 1, ft_putchar);
				g_msh.pos++;
			}
		}
		else if (!ft_strcmp(buf, "\177"))//backspace
		{
			if (g_msh.pos > 0)
			{
				g_msh.line = ft_del_chinstr(g_msh.line, g_msh.pos);
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
				g_msh.pos--;
			}
		}
		else if (!ft_strcmp(buf, "\n"))//enter
			break ;
		else if (!ft_strcmp(buf, "\4") && !ft_strlen(g_msh.line))
			return (0);
		else if (!ft_strcmp(buf, "\3"))//ctrl-c
		{
			g_msh.rdfl = 1;
			write(1, "\n", 1);
			return (0);
		}
		else
		{
			if (ft_isprint(buf[0]) && ft_strcmp(buf, "\t"))//except tab
			{
				tputs(tgetstr("im", 0), 1, ft_putchar);
				g_msh.line = ft_ins_ch2str(g_msh.line, buf[0], g_msh.pos);
				g_msh.pos++;
				write (1, buf, len);
				tputs(tgetstr("ei", 0), 1, ft_putchar);
			}
		}
	}
	return (1);
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
