#include "minishell.h"

char	*del_start_sp(char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	while (s1[i] == ' ')
		i++;
	s2 = ft_cutline(s1, i);
	return (s2);
}

int		get_envname_len(char *s)
{
	int		i;

	i = 0;
	while (ft_isalnum(s[i]))
		i++;
	return (i);
}

char	*get_env_name(void)
{
	char	*name;
	int		len;
	int		i;

	len = get_envname_len(g_msh.line);
	name = (char *)ft_calloc(sizeof(char), (len + 1));//if name = NULL
	i = 0;
	while (ft_isalnum(g_msh.line[i]))
	{
		name[i] = g_msh.line[i];
		i++;
	}
	g_msh.line = ft_cutline(g_msh.line, i);
	return (name);
}

int		get_sqstr_len(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\'')
		i++;
	return (i);
}

char	*get_sq_str(void)
{
	char	*str;
	int		len;
	int		i;

	len = get_sqstr_len(g_msh.line);
	str = (char *)ft_calloc(sizeof(char), (len + 1));//if str=NULL
	i = 0;
	while (g_msh.line[i] != '\'')
	{
		str[i] = g_msh.line[i];
		i++;
	}
	g_msh.line = ft_cutline(g_msh.line, (i + 1));
	return (str);
}

void	args2lower(t_pars *pars)
{
	int		i;

	i = 0;
	while (pars->args[0][i] != '\0')
	{
		pars->args[0][i] = ft_tolower(pars->args[0][i]);
		i++;
	}
}

void	dollar_pars(t_pars *pars)
{
	char	*env_name;
	char	*env_val;

	g_msh.line = ft_cutline(g_msh.line, (pars->n + 1));
	pars->n = 0;
	env_name = get_env_name();
	env_val = env_value(g_msh.envp, env_name);
	free(env_name);
	env_name = NULL;
	pars->args[pars->j] = ft_strjoin_fr(pars->args[pars->j], env_val);
	free(env_val);
	env_val = NULL;
}

void	strongquotes_pars(t_pars *pars)
{
	char	*sq_str;

	g_msh.line = ft_cutline(g_msh.line, (pars->n + 1));
	pars->n = 0;
	//check for 2nd ' -> search line
	sq_str = get_sq_str();
	pars->args[pars->j] = ft_strjoin_fr(pars->args[pars->j], sq_str);
	free(sq_str);
	sq_str = NULL;
}

void	weakquotes_pars(t_pars *pars)
{
	g_msh.line = ft_cutline(g_msh.line, (pars->n + 1));
	pars->n = 0;
	while (g_msh.line[pars->n] != '\"')
	{
		if (g_msh.line[pars->n] == '\\' && g_msh.line[pars->n + 1] == '\\')
		{
			g_msh.line = ft_cutline(g_msh.line, (pars->n + 2));
			pars->args[pars->j] = ft_strjoin_fr(pars->args[pars->j], "\\");
			pars->n = 0;
		}
		else if (g_msh.line[pars->n] == '\\' && g_msh.line[pars->n + 1] == '\"')
		{
			g_msh.line = ft_cutline(g_msh.line, (pars->n + 2));
			pars->args[pars->j] = ft_strjoin_fr(pars->args[pars->j], "\"");
			pars->n = 0;
		}
		else if (g_msh.line[pars->n] == '\\' && g_msh.line[pars->n + 1] == '$')
		{
			g_msh.line = ft_cutline(g_msh.line, (pars->n + 2));
			pars->args[pars->j] = ft_strjoin_fr(pars->args[pars->j], "$");
			pars->n = 0;
		}
		else
		{
			pars->args[pars->j] = ft_add_char2str(pars->args[pars->j], g_msh.line[pars->n]);
			g_msh.line = ft_cutline(g_msh.line, (pars->n + 1));
			pars->n = 0;
		}
	}
	g_msh.line = ft_cutline(g_msh.line, (pars->n + 1));
}

void	backslash_pars(t_pars *pars)
{
	pars->args[pars->j] = ft_add_char2str(pars->args[pars->j], g_msh.line[1]);
	g_msh.line = ft_cutline(g_msh.line, (pars->n + 2));
	pars->n = 0;
}

void	space_pars(t_pars *pars)
{
	while (g_msh.line[pars->n] == ' ')
		pars->n++;
	if (g_msh.line[pars->n] != '\0')
	{
		pars->args = add_str2darr(pars->args);
		pars->j++;
	}
	g_msh.line = ft_cutline(g_msh.line, pars->n);
	pars->n = 0;
}

void	enlarge_arg(t_pars *pars)
{
	pars->args[pars->j] = ft_add_char2str(pars->args[pars->j], g_msh.line[pars->n]);
	g_msh.line = ft_cutline(g_msh.line, (pars->n + 1));
	pars->n = 0;
}

void	parser(void)
{
	t_pars	pars;

	ft_bzero(&pars, sizeof(t_pars));
	g_msh.line = del_start_sp(g_msh.line);
	pars.args = (char **)ft_calloc(sizeof(char *), 2);//if args = NULL
	pars.args[pars.j] = (char *)ft_calloc(sizeof(char), 1);//if args[] = NULL
	while (g_msh.line[pars.n] != '\0')
	{
		if (g_msh.line[pars.n] == '$')
			dollar_pars(&pars);
		else if (g_msh.line[pars.n] == '\'')
			strongquotes_pars(&pars);
		else if (g_msh.line[pars.n] == '\"')
			weakquotes_pars(&pars);
		else if (g_msh.line[pars.n] == '\\')//check if no symbol after '\'
			backslash_pars(&pars);
		else if (g_msh.line[pars.n] == ' ')
			space_pars(&pars);
		else
			enlarge_arg(&pars);
	}
	args2lower(&pars);

	if (!ft_strlen(pars.args[0]))
		g_msh.status = 0;
	else
	{
		// executor(msh, &pars); ---------------------------------------------for Vlad

		//// test print line & args ////
		write(1, g_msh.line, ft_strlen(g_msh.line));
		write(1, "\n", 1);
		int i;
		i = 0;
		while (pars.args[i] != NULL)
		{
			write(1, pars.args[i], ft_strlen(pars.args[i]));
			write(1, "\n", 1);
			i++;
		}
		g_msh.status = 1;
		free(g_msh.line);
		////
	}
}