#include "minishell.h"

void	dollar_pars_rd(t_pars *pars)
{
	char	*env_name;
	char	*env_val;

	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	env_name = get_env_name(pars);
	env_val = env_value(g_msh.envp, env_name);
	free(env_name);
	env_name = NULL;
	pars->rds = ft_strjoin_fr(pars->rds, env_val);
	change_sp2us(&env_val);
	g_msh.check_sprds = ft_strjoin_fr(g_msh.check_sprds, env_val);
	free(env_val);
	env_val = NULL;
}

void	strongquotes_pars_rd(t_pars *pars)
{
	char	*sq_str;

	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	sq_str = get_sq_str(pars);
	pars->rds = ft_strjoin_fr(pars->rds, sq_str);
	change_sp2us(&sq_str);
	g_msh.check_sprds = ft_strjoin_fr(g_msh.check_sprds, sq_str);
	free(sq_str);
	sq_str = NULL;
}

void	backslash_pars_rd(t_pars *pars)
{
	pars->rds = ft_add_char2str(pars->rds, pars->s[1]);
	g_msh.check_sprds = ft_add_char2str(g_msh.check_sprds, pars->s[1]);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->i = 0;
}
