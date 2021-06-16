#include "minishell.h"

void	args2lower(void)
{
	int		i;
	int		n;

	i = 0;
	while(i < g_msh.pipe_count)
	{
		n = 0;
		if (g_msh.pipe[i].args != NULL)
		{
			if (g_msh.pipe[i].args[0] != NULL)
			{
				while(g_msh.pipe[i].args[0][n] != '\0')
				{
					g_msh.pipe[i].args[0][n] = ft_tolower(g_msh.pipe[i].args[0][n]);
					n++;
				}
			}
		}
		i++;
	}
}

int		get_pipe_num(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	g_msh.flags = NOFLG;
	while (s[i])
	{
		set_flags(s[i]);
		if (s[i] == '|' && !check_flags())
			n++;
		i++;
	}
	return (n);
}

int		get_sqstr_len(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\'')
		i++;
	return (i);
}

char	*get_sq_str(t_pars *pars)
{
	char	*str;
	int		len;
	int		i;

	len = get_sqstr_len(pars->s);
	str = (char *)ft_calloc(sizeof(char), (len + 1));//if str=NULL
	if (str == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	i = 0;
	while (pars->s[i] != '\'')
	{
		str[i] = pars->s[i];
		i++;
	}
	pars->s = ft_cutstr_begin(pars->s, (i + 1));
	return (str);
}

void	strongquotes_pars(t_pars *pars)
{
	char	*sq_str;

	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	sq_str = get_sq_str(pars);
	pars->args = ft_strjoin_fr(pars->args, sq_str);
	change_sp2us(&sq_str);
	g_msh.check_spargs = ft_strjoin_fr(g_msh.check_spargs, sq_str);
	free(sq_str);
	sq_str = NULL;
}

void	backslash_pars(t_pars *pars)
{
	pars->args = ft_add_char2str(pars->args, pars->s[1]);
	g_msh.check_spargs = ft_add_char2str(g_msh.check_spargs, pars->s[1]);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->i = 0;
}

void	space_pars(t_pars *pars)
{
	while (pars->s[pars->i] == ' ')
		pars->i++;
	pars->s = ft_cutstr_begin(pars->s, pars->i);
	pars->args = ft_add_char2str(pars->args, ' ');
	g_msh.check_spargs = ft_add_char2str(g_msh.check_spargs, ' ');
	pars->i = 0;
}

void	enlarge_args(t_pars *pars)
{
 	pars->args = ft_add_char2str(pars->args, pars->s[pars->i]);
	g_msh.check_spargs = ft_add_char2str(g_msh.check_spargs, pars->s[pars->i]);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
}

int		get_pipestr_len(char *s)
{
	int	i;

	i = 0;
	g_msh.flags = NOFLG;
	while(s[i])
	{
		set_flags(s[i]);
		if (s[i] == '|' && !check_flags())
			break;
		i++;
	}
	return (i);
}

char	*get_pipe_str(char **s)
{
	char	*tmp;
	int		len;

	len = get_pipestr_len(*s);
	tmp = ft_substr(*s, 0, len);
	if (tmp == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	if ((*s)[len] == '|')
		*s = ft_cutstr_begin(*s, (len + 1));
	return (tmp);
}

void	lexer(t_pars *pars)
{
	g_msh.check_spargs = ft_strnew(0);
	g_msh.check_sprds = ft_strnew(0);

	while(pars->s[pars->i] != '\0')
	{
		if (pars->s[pars->i] == '>' || pars->s[pars->i] == '<')
			redir_pars(pars);

		else if (pars->s[pars->i] == '$')
			dollar_pars(pars);
		else if (pars->s[pars->i] == '\'')
			strongquotes_pars(pars);
		else if (pars->s[pars->i] == '\"')
			weakquotes_pars(pars);
		else if (pars->s[pars->i] == '\\')//check if no symbol after '\'
			backslash_pars(pars);

		else if (pars->s[pars->i] == ' ')
			space_pars(pars);
		else
			enlarge_args(pars);
	}
}

void	fill_pars(t_pars *pars)
{
	pars->s = del_start_sp(pars->s);
	pars->s = del_end_sp(pars->s);
	lexer(pars);

	// ///////
	// printf("args  # %s\n", pars->args);
	// printf("spargs# %s\n", g_msh.check_spargs);
	// printf("rds  # %s\n", pars->rds);
	// printf("sprds# %s\n", g_msh.check_sprds);
	// ///////
}

void	parser(char *s)
{
	t_pars	pars;
	int		i;
	
	ft_bzero(&pars, sizeof(t_pars));

	i = 0;
	while(i < g_msh.pipe_count)
	{
		pars.s = get_pipe_str(&s);
		pars.args = ft_strnew(0);
		pars.rds = ft_strnew(0);
		pars.i = 0;

		fill_pars(&pars);

		g_msh.pipe[i].args = ft_spargs_split(pars.args);
		if (g_msh.pipe[i].args == NULL)
			error_func(ERROR_MEM, 1, 0, NULL);
		g_msh.pipe[i].rd = ft_sprds_split(pars.rds);
		if (g_msh.pipe[i].rd == NULL)
			error_func(ERROR_MEM, 1, 0, NULL);

		repair_empty_rd();

		g_msh.pipe[i].bin_path = path_finder(env_value(g_msh.envp, "PATH"), g_msh.pipe[i].args[0]);

		free(g_msh.check_spargs);
		free(g_msh.check_sprds);

		free(pars.s);
		free(pars.args);
		free(pars.rds);
		i++;
	}
	free(s);
	args2lower();
}

void	launch(void)
{
	int	n;

	n = 0;
	while (g_msh.semi[n] != NULL)
	{
		g_msh.pipe_count = get_pipe_num(g_msh.semi[n]) + 1;

		if (!check_syntax(g_msh.semi[n]))
		{
			n++;
			continue;
		}

		g_msh.pipe = (t_pipe *)ft_calloc((g_msh.pipe_count + 1), sizeof(t_pipe));
		if (g_msh.pipe == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);

		parser(g_msh.semi[n]);

		// ////////print g_msh.pipe[]
		// int	i = 0;
		// while(i < g_msh.pipe_count)
		// {
		// 	printf("pipe[%d]\n", i);
		// 	int n = 0;
		// 	while(g_msh.pipe[i].args[n] != NULL)
		// 	{
		// 		printf("  args#%s\n", g_msh.pipe[i].args[n]);
		// 		n++;
		// 	}
		// 	n = 0;
		// 	while(g_msh.pipe[i].rd[n] != NULL)
		// 	{
		// 		printf("  rd#%s\n", g_msh.pipe[i].rd[n]);
		// 		n++;
		// 	}
		// 	printf("********************\n");
		// 	i++;
		// }
		// /////////////////////////

		executor();
		free_pipe();
		n++;
	}
	free(g_msh.semi);
}


///////////////////////////////
// int main()//test part
// {
// 	char *s;
// 	char *tmp = "ecHo $USER > \"file1\" < 'file2' b'>'bb | cCc >> fi'<'le3 \\ddd";
// 	s = strdup(tmp);
// 	parser(s);
// 	// while(1);//leaks loop

// 	////////print g_msh.pipe[]
// 	int	i = 0;
// 	while(i < g_msh.pipe_count)
// 	{
// 		printf("pipe[%d]\n", i);
// 		int n = 0;
// 		while(g_msh.pipe[i].args[n] != NULL)
// 		{
// 			printf("  args#%s\n", g_msh.pipe[i].args[n]);
// 			n++;
// 		}
// 		n = 0;
// 		while(g_msh.pipe[i].rd[n] != NULL)
// 		{
// 			printf("  rd#%s\n", g_msh.pipe[i].rd[n]);
// 			n++;
// 		}
// 		printf("********************\n");
// 		i++;
// 	}
// }