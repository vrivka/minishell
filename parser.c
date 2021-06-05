#include "minishell.h"

void	args2lower(void)
{
	int		i;
	int		n;

	i = 0;
	while(i < g_msh.pipe_count)
	{
		n = 0;
		if (g_msh.pipe[i].args != NULL)
		{
			if (g_msh.pipe[i].args[0] != NULL)
			{
				while(g_msh.pipe[i].args[0][n] != '\0')
				{
					g_msh.pipe[i].args[0][n] = ft_tolower(g_msh.pipe[i].args[0][n]);
					n++;
				}
			}
		}
		i++;
	}
}

int		get_pipe_num(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	g_msh.flags = NOFLG;
	while (s[i])
	{
		set_flags(s[i]);
		if (s[i] == '|' && !check_flags())
			n++;
		i++;
	}
	return (n);
}

char	*del_start_sp(char *s1)
{
	char	*s2;
	int		i;

	s2 = NULL;
	i = 0;
	if (s1[i] == ' ')
	{
		while (s1[i] == ' ')
			i++;
		s2 = ft_cutstr_begin(s1, i);
		return (s2);
	}
	return (s1);
}

char	*del_end_sp(char *s1)
{
	char	*s2;
	int		i;
	int		len;

	s2 = NULL;
	len = ft_strlen(s1);
	i = len - 1;
	if (s1[i] == ' ')
	{
		while (s1[i] == ' ')
			i--;
		s2 = ft_cutstr_end(s1, (i + 1));
		return (s2);
	}
	return (s1);
}

int		get_envname_len(char *s)
{
	int		i;

	i = 0;
	while (ft_isalnum(s[i]))
		i++;
	return (i);
}

char	*get_env_name(t_pars *pars)
{
	char	*name;
	int		len;
	int		i;

	len = get_envname_len(pars->s);
	name = (char *)ft_calloc(sizeof(char), (len + 1));//if name = NULL
	i = 0;
	while (ft_isalnum(pars->s[i]))
	{
		name[i] = pars->s[i];
		i++;
	}
	pars->s = ft_cutstr_begin(pars->s, i);
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

char	*get_sq_str(t_pars *pars)
{
	char	*str;
	int		len;
	int		i;

	len = get_sqstr_len(pars->s);
	str = (char *)ft_calloc(sizeof(char), (len + 1));//if str=NULL
	i = 0;
	while (pars->s[i] != '\'')
	{
		str[i] = pars->s[i];
		i++;
	}
	pars->s = ft_cutstr_begin(pars->s, (i + 1));
	return (str);
}

void	dollar_pars(t_pars *pars)
{
	char	*env_name;
	char	*env_val;

	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	env_name = get_env_name(pars);
	env_val = env_value(g_msh.envp, env_name);
	free(env_name);
	env_name = NULL;
	pars->args = ft_strjoin_fr(pars->args, env_val);
	free(env_val);
	env_val = NULL;
}

void	strongquotes_pars(t_pars *pars)
{
	char	*sq_str;

	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	//check for 2nd ' -> search line
	sq_str = get_sq_str(pars);
	pars->args = ft_strjoin_fr(pars->args, sq_str);
	free(sq_str);
	sq_str = NULL;
}

void	weakquotes_pars(t_pars *pars)
{
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
	while (pars->s[pars->i] != '\"')
	{
		if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '\\')
		{
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
			pars->args = ft_strjoin_fr(pars->args, "\\");
			pars->i = 0;
		}
		else if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '\"')
		{
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
			pars->args = ft_strjoin_fr(pars->args, "\"");
			pars->i = 0;
		}
		else if (pars->s[pars->i] == '\\' && pars->s[pars->i + 1] == '$')
		{
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
			pars->args = ft_strjoin_fr(pars->args, "$");
			pars->i = 0;
		}
		else
		{
			pars->args = ft_add_char2str(pars->args, pars->s[pars->i]);
			pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
			pars->i = 0;
		}
	}
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
}

void	backslash_pars(t_pars *pars)
{
	pars->args = ft_add_char2str(pars->args, pars->s[1]);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 2));
	pars->i = 0;
}

void	space_pars(t_pars *pars)
{
	while (pars->s[pars->i] == ' ')
		pars->i++;
	pars->s = ft_cutstr_begin(pars->s, pars->i);
	pars->args = ft_add_char2str(pars->args, ' ');
	pars->i = 0;
}

void	enlarge_args(t_pars *pars)
{
 	pars->args = ft_add_char2str(pars->args, pars->s[pars->i]);
	pars->s = ft_cutstr_begin(pars->s, (pars->i + 1));
	pars->i = 0;
}

int		get_pipestr_len(char *s)
{
	int	i;

	i = 0;
	g_msh.flags = NOFLG;
	while(s[i])
	{
		set_flags(s[i]);
		if (s[i] == '|' && !check_flags())
			break;
		i++;
	}
	return (i);
}

char	*get_pipe_str(char **s)
{
	char	*tmp;
	int		len;

	len = get_pipestr_len(*s);
	tmp = ft_substr(*s, 0, len);
	if ((*s)[len] == '|')
		*s = ft_cutstr_begin(*s, (len + 1));
	return (tmp);
}

void	lexer(t_pars *pars)
{
	while(pars->s[pars->i] != '\0')
	{
		if (pars->s[pars->i] == '>' || pars->s[pars->i] == '<')
			redir_pars(pars);

		else if (pars->s[pars->i] == '$')//only letters,numbers and _ after $
			dollar_pars(pars);
		else if (pars->s[pars->i] == '\'')
			strongquotes_pars(pars);
		else if (pars->s[pars->i] == '\"')
			weakquotes_pars(pars);
		else if (pars->s[pars->i] == '\\')//check if no symbol after '\'
			backslash_pars(pars);

		else if (pars->s[pars->i] == ' ')
			space_pars(pars);
		else
			enlarge_args(pars);
	}
}

void	fill_pars(t_pars *pars)
{
	pars->s = del_start_sp(pars->s);
	pars->s = del_end_sp(pars->s);
	lexer(pars);

	// ///////
	// printf("args# %s\n", pars->args);
	// printf("rds# %s\n", pars->rds);
	// ///////
}

void	parser(char *s)
{
	t_pars	pars;
	int		i;
	
	ft_bzero(&pars, sizeof(t_pars));

	g_msh.pipe_count = get_pipe_num(s) + 1;
	g_msh.pipe = (t_pipe *)ft_calloc((g_msh.pipe_count + 1), sizeof(t_pipe));// if == NULL

	i = 0;
	while(i < g_msh.pipe_count)
	{
		// init_pars(s);
		pars.s = get_pipe_str(&s);//take out part of s before | or \0
		pars.args = (char *)ft_calloc(1, sizeof(char));// if ==NULL
		pars.rds = (char *)ft_calloc(1, sizeof(char));// if ==NULL
		pars.i = 0;
		//

		fill_pars(&pars);

		g_msh.pipe[i].args = ft_split(pars.args, ' ');
		g_msh.pipe[i].rd = ft_split(pars.rds, ' ');
		// g_msh.pipe.bin_path = ;

		free(pars.s);
		free(pars.args);
		free(pars.rds);
		i++;
	}
	free(s);
	args2lower();
}

void	launch(void)
{
	int	n;

	n = 0;
	while (g_msh.semi[n])
	{
		parser(g_msh.semi[n]);
		executor();//---------------------------------------------for Vlad
		//free pipe
	}
	free_d_arr(g_msh.semi);
}


///////////////////////////////
// int main()//test part
// {
// 	char *s;
// 	char *tmp = "ecHo $USER > \"file1\" < 'file2' b'>'bb | cCc >> fi'<'le3 \\ddd";
// 	s = strdup(tmp);
// 	parser(s);
// 	// while(1);//leaks loop

// 	////////print g_msh.pipe[]
// 	int	i = 0;
// 	while(i < g_msh.pipe_count)
// 	{
// 		printf("pipe[%d]\n", i);
// 		int n = 0;
// 		while(g_msh.pipe[i].args[n] != NULL)
// 		{
// 			printf("  args#%s\n", g_msh.pipe[i].args[n]);
// 			n++;
// 		}
// 		n = 0;
// 		while(g_msh.pipe[i].rd[n] != NULL)
// 		{
// 			printf("  rd#%s\n", g_msh.pipe[i].rd[n]);
// 			n++;
// 		}
// 		printf("********************\n");
// 		i++;
// 	}
// }