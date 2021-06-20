#include "minishell.h"

void	free_tmp_vars(t_pars *pars)
{
	free(g_msh.check_spargs);
	free(g_msh.check_sprds);
	free(pars->s);
	free(pars->args);
	free(pars->rds);
}

void	fill_pars(t_pars *pars)
{
	pars->s = del_start_sp(pars->s);
	pars->s = del_end_sp(pars->s);
	lexer(pars);
}

void	pars_init(t_pars *pars)
{
	pars->args = ft_strnew(0);
	pars->rds = ft_strnew(0);
	pars->i = 0;
}

void	parser(char *s)
{
	t_pars	pars;
	int		i;

	ft_bzero(&pars, sizeof(t_pars));
	i = 0;
	while (i < g_msh.pipe_count)
	{
		pars.s = get_pipe_str(&s);
		pars_init(&pars);
		fill_pars(&pars);
		g_msh.pipe[i].args = ft_spargs_split(pars.args);
		if (g_msh.pipe[i].args == NULL)
			error_func(ERROR_MEM, 1, 0, NULL);
		g_msh.pipe[i].rd = ft_sprds_split(pars.rds);
		if (g_msh.pipe[i].rd == NULL)
			error_func(ERROR_MEM, 1, 0, NULL);
		repair(i);
		g_msh.pipe[i].bin_path = \
		path_finder(env_value(g_msh.envp, "PATH"), g_msh.pipe[i].args[0]);
		free_tmp_vars(&pars);
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
			free(g_msh.semi[n]);
			n++;
			continue ;
		}
		g_msh.pipe = \
		(t_pipe *)ft_calloc((g_msh.pipe_count + 1), sizeof(t_pipe));
		if (g_msh.pipe == NULL)
			error_func(ERROR_MEM, 1, 0, NULL);
		parser(g_msh.semi[n]);
		executor();
		free_pipe();
		n++;
	}
	free(g_msh.semi);
}
