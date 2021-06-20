#include "minishell.h"

void	wq_bsbs_pars(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->args = ft_strjoin_fr(pars->args, "\\");
	g_msh.check_spargs = ft_strjoin_fr(g_msh.check_spargs, "\\");
	pars->i = 0;
}

void	wq_bswq_pars(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->args = ft_strjoin_fr(pars->args, "\"");
	g_msh.check_spargs = ft_strjoin_fr(g_msh.check_spargs, "\"");
	pars->i = 0;
}

void	wq_bsdol_pars(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->args = ft_strjoin_fr(pars->args, "$");
	g_msh.check_spargs = ft_strjoin_fr(g_msh.check_spargs, "$");
	pars->i = 0;
}

void	wq_dolbs_pars(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->args = ft_strjoin_fr(pars->args, "$\\");
	g_msh.check_spargs = ft_strjoin_fr(g_msh.check_spargs, "$\\");
	pars->i = 0;
}

void	wq_doldig_pars(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->i = 0;
}
