#include "minishell.h"

void	wq_dollar_val(t_pars *pars)
{
	char	*env_name;
	char	*env_val;

	env_name = ft_strnew(0);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	while (pars->s[pars->i] != '\"' && pars->s[pars->i] != '\'')
	{
		if (pars->s[pars->i] == ' ')
			break ;
		env_name = ft_add_char2str(env_name, pars->s[pars->i]);
		pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
		pars->i = 0;
	}
	env_val = env_value(g_msh.envp, env_name);
	if (env_val != NULL)
	{
		pars->args = ft_strjoin_fr(pars->args, env_val);
		change_sp2us(&env_val);
		g_msh.check_spargs = ft_strjoin_fr(g_msh.check_spargs, env_val);
		free(env_val);
	}
	free(env_name);
}

void	wq_dollar_ret(t_pars *pars)
{
	char	*ret;

	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->i = 0;
	ret = ft_itoa(g_msh.ret);
	if (ret == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	pars->args = ft_strjoin_fr(pars->args, ret);
	g_msh.check_spargs = ft_strjoin_fr(g_msh.check_spargs, ret);
	if (ret != NULL)
		free(ret);
}

void	wq_enlarge_args(t_pars *pars)
{
	pars->args = ft_add_char2str(pars->args, pars->s[pars->i]);
	if (pars->s[pars->i] == ' ')
		g_msh.check_spargs = ft_add_char2str(g_msh.check_spargs, '_');
	else
		g_msh.check_spargs = \
		ft_add_char2str(g_msh.check_spargs, pars->s[pars->i]);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
}

void	weakquotes_pars(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	while (pars->s[pars->i] != '\"')
	{
		if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '\\')
			wq_bsbs_pars(pars);
		else if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '\"')
			wq_bswq_pars(pars);
		else if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '$')
			wq_bsdol_pars(pars);
		else if (pars->s[pars->i] == '$' && pars->s[pars->i + 1] == '\\')
			wq_dolbs_pars(pars);
		else if (pars->s[pars->i] == '$' && ft_isdigit(pars->s[pars->i + 1]))
			wq_doldig_pars(pars);
		else if (pars->s[pars->i] == '$' && pars->s[pars->i + 1] == '?')
			wq_dollar_ret(pars);
		else if ((pars->s[pars->i] == '$' && ft_isalpha(pars->s[pars->i + 1])))
			wq_dollar_val(pars);
		else
			wq_enlarge_args(pars);
	}
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
}
