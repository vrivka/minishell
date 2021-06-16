#include "minishell.h"

char	*get_env_name(t_pars *pars)
{
	char	*name;

	name = ft_strnew(0);
	while (pars->s[pars->i] != '\0' && pars->s[pars->i] != ' ')
	{
		if (ft_strchr("\'\"\\=", pars->s[pars->i]))
			break ;
		else if (pars->s[pars->i] == '?')
		{
			name = ft_add_char2str(name, '?');
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
			pars->i = 0;
			break ;
		}
		name = ft_add_char2str(name, pars->s[pars->i]);
		pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
		pars->i = 0;
	}
	return (name);
}
