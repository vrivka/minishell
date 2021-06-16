#include "minishell.h"

void	wq_bsbs_pars_rd(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->rds = ft_strjoin_fr(pars->rds, "\\");
	g_msh.check_sprds = ft_strjoin_fr(g_msh.check_sprds, "\\");
	pars->i = 0;
}

void	wq_bswq_pars_rd(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->rds = ft_strjoin_fr(pars->rds, "\"");
	g_msh.check_sprds = ft_strjoin_fr(g_msh.check_sprds, "\"");
	pars->i = 0;
}

void	wq_bsdol_pars_rd(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->rds = ft_strjoin_fr(pars->rds, "$");
	g_msh.check_sprds = ft_strjoin_fr(g_msh.check_sprds, "$");
	pars->i = 0;
}

void	weakquotes_pars_rd(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	while (pars->s[pars->i] != '\"')
	{
		if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '\\')
			wq_bsbs_pars_rd(pars);
		else if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '\"')
			wq_bswq_pars_rd(pars);
		else if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '$')
			wq_bsdol_pars_rd(pars);
		else
		{
			pars->rds = ft_add_char2str(pars->rds, pars->s[pars->i]);
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
			if (pars->s[pars->i] == ' ')
				g_msh.check_sprds = ft_add_char2str(g_msh.check_sprds, '_');
			else
				g_msh.check_sprds = \
				ft_add_char2str(g_msh.check_sprds, pars->s[pars->i]);
			pars->i = 0;
		}
	}
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
}
