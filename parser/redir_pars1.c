#include "minishell.h"

void	place_space(t_pars *pars)
{
	pars->rds = ft_add_char2str(pars->rds, ' ');
	g_msh.check_sprds = ft_add_char2str(g_msh.check_sprds, ' ');
}

void	place_rd_symbols(t_pars *pars)
{
	pars->rds = ft_add_char2str(pars->rds, pars->s[pars->i]);
	g_msh.check_sprds = \
	ft_add_char2str(g_msh.check_sprds, pars->s[pars->i]);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
}

void	space_pars_rd(t_pars *pars)
{
	while (pars->s[pars->i] == ' ')
		pars->i++;
	pars->s = ft_cutstr_begin(pars->s, pars->i);
	pars->i = 0;
}

void	enlarge_rds(t_pars *pars)
{
	pars->rds = ft_add_char2str(pars->rds, pars->s[pars->i]);
	g_msh.check_sprds = ft_add_char2str(g_msh.check_sprds, pars->s[pars->i]);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
}

void	redir_pars(t_pars *pars)
{
	while (ft_strchr("<>", pars->s[pars->i]))
		place_rd_symbols(pars);
	place_space(pars);
	if (pars->s[pars->i] == ' ')
		space_pars_rd(pars);
	while (pars->s[pars->i] != '\0' && pars->s[pars->i] != ' ')
	{
		if (pars->s[pars->i] == '<' || pars->s[pars->i] == '>')
			break ;
		else if (pars->s[pars->i] == '$')
			dollar_pars_rd(pars);
		else if (pars->s[pars->i] == '\'')
			strongquotes_pars_rd(pars);
		else if (pars->s[pars->i] == '\"')
			weakquotes_pars_rd(pars);
		else if (pars->s[pars->i] == '\\')
			backslash_pars_rd(pars);
		else
			enlarge_rds(pars);
	}
	place_space(pars);
}
