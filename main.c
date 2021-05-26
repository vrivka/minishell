#include "minishell.h"

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}	

void	term_setup(t_msh *msh)//when exit return term settings back!
{
	struct	termios term;

	msh->term = &term;
	msh->term_name = getenv("TERM");//"xterm-256color"
	// if (msh->term == NULL)
	// 	Can`t get terminal type from environment
	tcgetattr(0, msh->term);//return 0 or -1
	msh->term->c_lflag &= ~(ECHO);
	msh->term->c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, msh->term);//return 0 or -1
	tgetent(0, msh->term_name);//return 0 or -1
}

void	copy_envs(t_msh *msh, char **envp)
{
	size_t	j;
	size_t	i;
	size_t	len;

	j = 0;
	while (envp[j] != NULL)
		j++;
	msh->envp = (char **)ft_calloc(sizeof(char *), (j + 1));
	j = 0;
	while (envp[j] != NULL)
	{
		len = ft_strlen(envp[j]);
		msh->envp[j] = (char *)ft_calloc(sizeof(char), (len + 1));
		i = 0;
		while (envp[j][i] != '\0')
		{
			msh->envp[j][i] = envp[j][i];
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

void	init_msh(t_msh *msh, char **av, char **envp)
{
	ft_bzero(msh, sizeof(t_msh));
	msh->status = 1;
	copy_envs(msh, envp);
	get_history(msh, av);
	msh->h_size = count_arr_lines(msh->history);
	msh->h_index = msh->h_size - 1;
}

void	key_loop(t_msh *msh)
{
	char	buf[BUFFER_SIZE];
	int		len;

	while (1)
	{
		ft_memset(buf, 0, BUFFER_SIZE);
		len = read(0, buf, BUFFER_SIZE);
		if (!ft_strcmp(buf, "\e[A"))//up
		{
			if (msh->h_index >= 0)
			{
				msh->pos = 0;
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tgetstr("ce", 0), 1, ft_putchar);
				write(1, msh->history[msh->h_index], ft_strlen(msh->history[msh->h_index]));
				msh->pos += ft_strlen(msh->history[msh->h_index]);
				msh->line = ft_strrewrite(msh->line, msh->history[msh->h_index]);
				if (msh->h_index > 0)
					msh->h_index--;
			}
		}
		else if (!ft_strcmp(buf, "\e[B"))//down
		{
			if (msh->h_index < msh->h_size)
			{
				msh->pos = 0;
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tgetstr("ce", 0), 1, ft_putchar);
				write(1, msh->history[msh->h_index], ft_strlen(msh->history[msh->h_index]));
				msh->pos += ft_strlen(msh->history[msh->h_index]);
				msh->line = ft_strrewrite(msh->line, msh->history[msh->h_index]);
				if (msh->h_index < (msh->h_size - 1))
					msh->h_index++;
			}
		}
		else if (!ft_strcmp(buf, "\177"))//backspace
		{
			if (msh->pos > 0)
			{
				msh->line = ft_strdellstch_fr(msh->line);
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
				msh->pos--;
			}
		}
		else if (!ft_strcmp(buf, "\t"))//tab
			continue ;
		else if (!ft_strcmp(buf, "\n"))//enter
			break;
		else
		{
			if (ft_isprint(buf[0]))
			{
				msh->line = ft_strjoin_fr(msh->line, buf);
				msh->pos++;
				write (1, buf, len);
			}
		}
	}
}

void	main_loop(t_msh *msh)
{
	msh->line = (char *)ft_calloc(sizeof(char), 1);
	write(1, "msh$ ", 5);
	tputs(save_cursor, 1, ft_putchar);
	// tputs(tgetstr("im", 0), 1, ft_putchar);
	key_loop(msh);
	insert_nline2hist(msh);
	// msh->history = add_str2darr(msh->history);
	msh->h_size++;
	write(1, "\n", 1);
	parser(msh);
}

int		main(int ac, char **av, char **envp)
{
	t_msh	msh;

	(void)ac;
	init_msh(&msh, av, envp);
	term_setup(&msh);
	while (msh.status)//executor sets status: 0 if error, 1 if succes
		main_loop(&msh);
	put_hist2file(&msh);// final clean write history to file
	return 0;
}