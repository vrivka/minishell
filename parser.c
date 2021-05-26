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

char	*get_env_name(t_msh *msh)
{
	char	*name;
	int		len;
	int		i;

	len = get_envname_len(msh->line);
	name = (char *)ft_calloc(sizeof(char), (len + 1));//if name = NULL
	i = 0;
	while (ft_isalnum(msh->line[i]))
	{
		name[i] = msh->line[i];
		i++;
	}
	msh->line = ft_cutline(msh->line, i);
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

char	*get_sq_str(t_msh *msh)
{
	char	*str;
	int		len;
	int		i;

	len = get_sqstr_len(msh->line);
	str = (char *)ft_calloc(sizeof(char), (len + 1));//if str=NULL
	i = 0;
	while (msh->line[i] != '\'')
	{
		str[i] = msh->line[i];
		i++;
	}
	msh->line = ft_cutline(msh->line, (i + 1));
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

void	dollar_pars(t_msh *msh, t_pars *pars)
{
	char	*env_name;
	char	*env_val;

	msh->line = ft_cutline(msh->line, (pars->n + 1));
	pars->n = 0;
	env_name = get_env_name(msh);
	env_val = env_value(msh->envp, env_name);
	free(env_name);
	env_name = NULL;
	pars->args[pars->j] = ft_strjoin_fr(pars->args[pars->j], env_val);
	free(env_val);
	env_val = NULL;
}

void	strongquotes_pars(t_msh *msh, t_pars *pars)
{
	char	*sq_str;

	msh->line = ft_cutline(msh->line, (pars->n + 1));
	pars->n = 0;
	//check for 2nd ' -> search line
	sq_str = get_sq_str(msh);
	pars->args[pars->j] = ft_strjoin_fr(pars->args[pars->j], sq_str);
	free(sq_str);
	sq_str = NULL;
}

void	weakquotes_pars(t_msh *msh, t_pars *pars)
{
	msh->line = ft_cutline(msh->line, (pars->n + 1));
	pars->n = 0;
	while (msh->line[pars->n] != '\"')
	{
		if (msh->line[pars->n] == '\\' && msh->line[pars->n + 1] == '\\')
		{
			msh->line = ft_cutline(msh->line, (pars->n + 2));
			pars->args[pars->j] = ft_strjoin_fr(pars->args[pars->j], "\\");
			pars->n = 0;
		}
		else if (msh->line[pars->n] == '\\' && msh->line[pars->n + 1] == '\"')
		{
			msh->line = ft_cutline(msh->line, (pars->n + 2));
			pars->args[pars->j] = ft_strjoin_fr(pars->args[pars->j], "\"");
			pars->n = 0;
		}
		else if (msh->line[pars->n] == '\\' && msh->line[pars->n + 1] == '$')
		{
			msh->line = ft_cutline(msh->line, (pars->n + 2));
			pars->args[pars->j] = ft_strjoin_fr(pars->args[pars->j], "$");
			pars->n = 0;
		}
		else
		{
			pars->args[pars->j] = ft_add_char2str(pars->args[pars->j], msh->line[pars->n]);
			msh->line = ft_cutline(msh->line, (pars->n + 1));
			pars->n = 0;
		}
	}
	msh->line = ft_cutline(msh->line, (pars->n + 1));
}

void	backslash_pars(t_msh *msh, t_pars *pars)
{
	pars->args[pars->j] = ft_add_char2str(pars->args[pars->j], msh->line[1]);
	msh->line = ft_cutline(msh->line, (pars->n + 2));
	pars->n = 0;
}

void	space_pars(t_msh *msh, t_pars *pars)
{
	while (msh->line[pars->n] == ' ')
		pars->n++;
	if (msh->line[pars->n] != '\0')
	{
		pars->args = add_str2darr(pars->args);
		pars->j++;
	}
	msh->line = ft_cutline(msh->line, pars->n);
	pars->n = 0;
}

void	enlarge_arg(t_msh *msh, t_pars *pars)
{
	pars->args[pars->j] = ft_add_char2str(pars->args[pars->j], msh->line[pars->n]);
	msh->line = ft_cutline(msh->line, (pars->n + 1));
	pars->n = 0;
}

void	parser(t_msh *msh)
{
	t_pars	pars;

	ft_bzero(&pars, sizeof(t_pars));
	msh->line = del_start_sp(msh->line);
	pars.args = (char **)ft_calloc(sizeof(char *), 2);//if args = NULL
	pars.args[pars.j] = (char *)ft_calloc(sizeof(char), 1);//if args[] = NULL
	while (msh->line[pars.n] != '\0')
	{
		if (msh->line[pars.n] == '$')
			dollar_pars(msh, &pars);
		else if (msh->line[pars.n] == '\'')
			strongquotes_pars(msh, &pars);
		else if (msh->line[pars.n] == '\"')
			weakquotes_pars(msh, &pars);
		else if (msh->line[pars.n] == '\\')//check if no symbol after '\'
			backslash_pars(msh, &pars);
		else if (msh->line[pars.n] == ' ')
			space_pars(msh, &pars);
		else
			enlarge_arg(msh, &pars);
	}
	args2lower(&pars);

	// executor(msh, &pars); ---------------------------------------------for Vlad

	//// test print line & args ////
	write(1, msh->line, ft_strlen(msh->line));
	write(1, "\n", 1);
	int i;
	i = 0;
	while (pars.args[i] != NULL)
	{
		write(1, pars.args[i], ft_strlen(pars.args[i]));
		write(1, "\n", 1);
		i++;
	}
	msh->status = 1;
	free(msh->line);
	////
}