#include "minishell.h"

void	add_sq_str(t_pars *pars, char **str)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	while (pars->s[pars->i] != '\'')
	{
		*str = ft_add_char2str(*str, pars->s[pars->i]);
		pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
		pars->i = 0;
	}
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
}

void	add_wq_str(t_pars *pars, char **str)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	while (pars->s[pars->i] != '\"')
	{
		*str = ft_add_char2str(*str, pars->s[pars->i]);
		pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
		pars->i = 0;
	}
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
}

char	*get_dstr(t_pars *pars)
{
	char	*str;

	str = ft_strnew(0);
	while (pars->s[pars->i] != '\0' && \
	pars->s[pars->i] != ' ' && pars->s[pars->i] != '$')
	{
		if (pars->s[pars->i] == '\\')
		{
			str = ft_add_char2str(str, '$');
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
			pars->i = 0;
		}
		else if (pars->s[pars->i] == '\'')
			add_sq_str(pars, &str);
		else if (pars->s[pars->i] == '\"')
			add_wq_str(pars, &str);
		else
		{
			str = ft_add_char2str(str, pars->s[pars->i]);
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
			pars->i = 0;
		}
	}
	return (str);
}

char	*get_env_val(char *env_name, char *d_str)
{
	char	*env_val;

	env_val = NULL;
	if (ft_strlen(env_name) != 0)
	{
		if (!ft_strcmp(env_name, "?"))
			env_val = ft_itoa(g_msh.ret);
		else
			env_val = env_value(g_msh.envp, env_name);
	}
	else if (ft_strlen(env_name) == 0 && ft_strlen(d_str) == 0)
		env_val = ft_strdup("$");
	free(env_name);
	return (env_val);
}

void	dollar_pars(t_pars *pars)
{
	char	*env_name;
	char	*env_val;
	char	*d_str;

	env_val = NULL;
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	env_name = get_env_name(pars);
	d_str = get_dstr(pars);
	env_val = get_env_val(env_name, d_str);
	if (env_val != NULL)
	{
		pars->args = ft_strjoin_fr(pars->args, env_val);
		g_msh.check_spargs = ft_strjoin_fr(g_msh.check_spargs, env_val);
		free(env_val);
	}
	pars->args = ft_strjoin_fr(pars->args, d_str);
	change_sp2us(&d_str);
	g_msh.check_spargs = ft_strjoin_fr(g_msh.check_spargs, d_str);
	free(d_str);
}
