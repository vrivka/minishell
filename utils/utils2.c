#include "minishell.h"

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
	char	**tmp;
	char	*stri;

	g_msh.pwd = NULL;
	ft_bzero(&g_msh, sizeof(t_msh));
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

void	clean_line(void)
{
	g_msh.line = del_start_sp(g_msh.line);
	g_msh.line = del_end_sp(g_msh.line);
}
