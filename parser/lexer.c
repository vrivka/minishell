#include "minishell.h"

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

void	lexer(t_pars *pars)
{
	g_msh.check_spargs = ft_strnew(0);
	g_msh.check_sprds = ft_strnew(0);
	while (pars->s[pars->i] != '\0')
	{
		if (pars->s[pars->i] == '>' || pars->s[pars->i] == '<')
			redir_pars(pars);
		else if (pars->s[pars->i] == '$')
			dollar_pars(pars);
		else if (pars->s[pars->i] == '\'')
			strongquotes_pars(pars);
		else if (pars->s[pars->i] == '\"')
			weakquotes_pars(pars);
		else if (pars->s[pars->i] == '\\')
			backslash_pars(pars);
		else if (pars->s[pars->i] == ' ')
			space_pars(pars);
		else
			enlarge_args(pars);
	}
}
