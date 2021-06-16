#include "minishell.h"

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}	

void	term_setup(void)
{
	int	ret;

	g_msh.term = (struct termios *)ft_calloc(1, sizeof(struct termios));
	if (g_msh.term == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	g_msh.term_name = getenv("TERM");
	if (g_msh.term_name == NULL)
		error_func(ERR_TERMNAME, 1, 0, NULL);
	ret = tcgetattr(0, g_msh.term);
	if (ret == -1)
		error_func(ERR_TERMATTR, 1, 0, NULL);
	ret = tgetent(0, g_msh.term_name);
	if (ret == -1)
		error_func(ERR_TERMCAP, 1, 0, NULL);
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
	if (g_msh.envp == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	j = 0;
	while (envp[j] != NULL)
	{
		len = ft_strlen(envp[j]);
		g_msh.envp[j] = (char *)ft_calloc(sizeof(char), (len + 1));
		if (g_msh.envp[j] == NULL)
			error_func(ERROR_MEM, 1, 0, NULL);
		i = 0;
		while (envp[j][i] != '\0')
		{
			g_msh.envp[j][i] = envp[j][i];
			i++;
		}
		j++;
	}
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
	if (tmp == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	free(tmp[2]);
	stri = ft_itoa(shlvl());
	if (stri == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	tmp[2] = ft_strjoin("SHLVL=", stri);
	if (tmp[2] == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	free(stri);
	export_func(tmp);
	free_envc(tmp, 2);
}

void	unset_term(void)
{
	int	ret;

	g_msh.term->c_lflag &= ~(ECHO);
	g_msh.term->c_lflag &= ~(ICANON);
	ret = tcsetattr(0, TCSANOW, g_msh.term);
	if (ret == -1)
		error_func(ERR_SETTERM, 1, 0, NULL);
}

void	set_term(void)
{
	int	ret;

	g_msh.term->c_lflag |= ECHO;
	g_msh.term->c_lflag |= ICANON;
	ret = tcsetattr(0, TCSANOW, g_msh.term);
	if (ret == -1)
		error_func(ERR_SETTERM, 1, 0, NULL);
}

int	main_loop(void)
{
	g_msh.line = (char *)ft_calloc(sizeof(char), 1);
	if (g_msh.line == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	g_msh.history = add_str2darr(g_msh.history);
	g_msh.h_size = count_arr_lines(g_msh.history);
	g_msh.h_index = g_msh.h_size - 1;
	g_msh.pos = 0;
	unset_term();
	key_loop();
	write(1, "\n", 1);
	set_term();

	g_msh.line = del_start_sp(g_msh.line);
	g_msh.line = del_end_sp(g_msh.line);
	if (ft_strlen(g_msh.line) == 0)
	{
		free(g_msh.line);
		return (1);
	}
	else
	{
		semicolon_splitter();
		if (!check_semi())
		{
			free_d_arr(g_msh.semi);
			return (error_func(ERR_SYNTAX, 1, 1, ";\n"));
		}
		launch();
	}
	return (1);
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	init_msh(av, envp);
	term_setup();
	while (g_msh.status)
		g_msh.status = main_loop();
	put_hist2file();
	free(g_msh.term);
	return 0;
}
