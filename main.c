#include "minishell.h"

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}	

void	term_setup(void)//when exit return term settings back!
{
	struct	termios term;

	g_msh.term = &term;
	g_msh.term_name = getenv("TERM");//"xterm-256color"
	// if (msh->term == NULL)
	// 	Can`t get terminal type from environment
	tcgetattr(0, g_msh.term);//return 0 or -1
	g_msh.term->c_lflag &= ~(ECHO);
	g_msh.term->c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, g_msh.term);//return 0 or -1
	tgetent(0, g_msh.term_name);//return 0 or -1
}

void	copy_envs(char **envp)
{
	size_t	j;
	size_t	i;
	size_t	len;

	j = 0;
	while (envp[j] != NULL)
		j++;
	g_msh.envp = (char **)ft_calloc(sizeof(char *), (j + 1));
	j = 0;
	while (envp[j] != NULL)
	{
		len = ft_strlen(envp[j]);
		g_msh.envp[j] = (char *)ft_calloc(sizeof(char), (len + 1));
		i = 0;
		while (envp[j][i] != '\0')
		{
			g_msh.envp[j][i] = envp[j][i];
			i++;
		}
		j++;
	}
	// j = 0;
	// while (msh->envp[j] != NULL)//print env vars
	// {
	// 	printf("%s\n", msh->envp[j]);
	// 	j++;
	// }
}

void	init_msh(char **av, char **envp)
{
	char **tmp;
	char *stri;

	g_msh.pwd = NULL;
	ft_bzero(&g_msh, sizeof(t_msh));
	g_msh.status = 1;
	copy_envs(envp);
	get_history(av);
	g_msh.h_size = count_arr_lines(g_msh.history);
	g_msh.h_index = g_msh.h_size - 1;
	tmp = ft_split("export OLDPWD SHLVL", ' ');
	free(tmp[2]);
	stri = ft_itoa(shlvl());
	tmp[2] = ft_strjoin("SHLVL=", stri);
	free(stri);
	export_func(tmp);
	free_envc(tmp, 2);
}

void	key_loop(void)
{
	char	buf[BUFFER_SIZE];
	int		len;

	while (1)
	{
		ft_memset(buf, 0, BUFFER_SIZE);
		len = read(0, buf, BUFFER_SIZE);
		if (!ft_strcmp(buf, "\e[A"))//up
		{
			if (g_msh.h_index >= 0)
			{
				g_msh.pos = 0;
				if (g_msh.h_index > 0)
					g_msh.h_index--;
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tgetstr("ce", 0), 1, ft_putchar);
				write(1, g_msh.history[g_msh.h_index], ft_strlen(g_msh.history[g_msh.h_index]));
				g_msh.pos += ft_strlen(g_msh.history[g_msh.h_index]);
			}
		}
		else if (!ft_strcmp(buf, "\e[B"))//down
		{
			if (g_msh.h_index < g_msh.h_size)
			{
				g_msh.pos = 0;
				if (g_msh.h_index < (g_msh.h_size - 1))
					g_msh.h_index++;
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tgetstr("ce", 0), 1, ft_putchar);
				write(1, g_msh.history[g_msh.h_index], ft_strlen(g_msh.history[g_msh.h_index]));
				g_msh.pos += ft_strlen(g_msh.history[g_msh.h_index]);
			}
		}
		else if (!ft_strcmp(buf, "\177"))//backspace
		{
			if (g_msh.pos > 0)
			{
				g_msh.history[g_msh.h_index] = ft_del_chinstr(g_msh.history[g_msh.h_index], g_msh.pos);
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
				g_msh.pos--;
			}
		}
		else if (!ft_strcmp(buf, "\t"))//tab
			continue ;
		else if (!ft_strcmp(buf, "\n"))//enter
		{
			g_msh.history[g_msh.h_size - 1] = ft_strrewrite(g_msh.history[g_msh.h_size - 1], g_msh.history[g_msh.h_index]);
			g_msh.line = ft_strrewrite(g_msh.line, g_msh.history[g_msh.h_size - 1]);
			g_msh.pos = 0;
			break;
		}
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
			if (g_msh.pos < ft_strlen(g_msh.history[g_msh.h_index]))
			{
				tputs(tgetstr("nd", 0), 1, ft_putchar);
				g_msh.pos++;
			}
		}
		else
		{
			if (ft_isprint(buf[0]))//print
			{
				tputs(tgetstr("im", 0), 1, ft_putchar);
				g_msh.history[g_msh.h_index] = ft_ins_ch2str(g_msh.history[g_msh.h_index], buf[0], g_msh.pos);
				g_msh.pos++;
				write (1, buf, len);
				tputs(tgetstr("ei", 0), 1, ft_putchar);
			}
		}
	}
}

void	main_loop(void)
{
	g_msh.line = (char *)ft_calloc(sizeof(char), 1);
	g_msh.history = add_str2darr(g_msh.history);
	g_msh.h_size = count_arr_lines(g_msh.history);
	g_msh.h_index = g_msh.h_size - 1;
	write(1, "msh$ ", 5);
	tputs(save_cursor, 1, ft_putchar);
	key_loop();
	write(1, "\n", 1);

	g_msh.line = del_start_sp(g_msh.line);
	g_msh.line = del_end_sp(g_msh.line);
	if (ft_strlen(g_msh.line) == 0)
	{
		free(g_msh.line);
		return ;
	}
	else
	{
	semicolon_splitter();
	launch();
	}
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	init_msh(av, envp);
	term_setup();
	while (g_msh.status)//executor sets status: 0 if error, 1 if succes
		main_loop();
	put_hist2file();// final clean write history to file
	return 0;
}

// enter - segfault
