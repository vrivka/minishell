#include "minishell.h"

void	fill_pars(t_pars *pars)
{
	pars->s = del_start_sp(pars->s);
	pars->s = del_end_sp(pars->s);
	lexer(pars);
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
		if (g_msh.pipe[i].rd[0] != NULL)
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
			free(g_msh.semi[n]);
			continue ;
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