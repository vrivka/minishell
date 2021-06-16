#include "minishell.h"

int	check_semi(void)
{
	int	i;

	i = 0;
	while (i < g_msh.semi_count)
	{
		if (!ft_strlen(g_msh.semi[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_mid_pipe(char *tmp)
{
	int	i;

	g_msh.flags = NOFLG;
	i = 0;
	while (tmp[i])
	{
		set_flags(tmp[i]);
		if (tmp[i] == '|' && !check_flags())
		{
			i++;
			while(tmp[i] == ' ')
				i++;
			if (ft_strchr("<>;|", tmp[i]))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	check_pipe(char *s)
{
	char	*tmp;

	tmp = ft_strdup(s);
	if (tmp == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	tmp = del_start_sp(tmp);
	tmp = del_end_sp(tmp);
	if (tmp[0] == '|' || tmp[ft_strlen(tmp) - 1] == '|' || check_mid_pipe(tmp))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

int	check_sq(char *s)
{
	int	i;

	g_msh.flags = NOFLG;
	i = 0;
	while (s[i])
	{
		set_flags(s[i]);
		i++;
	}
	set_flags(s[i]);
	if (g_msh.flags & SQFLG)
		return (0);
	return (1);
}

int	check_wq(char *s)
{
	int	i;

	g_msh.flags = NOFLG;
	i = 0;
	while (s[i])
	{
		set_flags(s[i]);
		i++;
	}
	set_flags(s[i]);
	if (g_msh.flags & WQFLG)
		return (0);
	return (1);
}

int	check_rd(char *s)
{
	int	i;

	if (s[ft_strlen(s) - 1] == '>' || s[ft_strlen(s) - 1] == '<')
		return (0);
	g_msh.flags = NOFLG;
	i = 0;
	while (s[i])
	{
		set_flags(s[i]);
		if (s[i] == '>' && s[i + 1] == '<' && !check_flags())//><
			return (0);
		else if (s[i] == '<' && s[i + 1] == '>' && !check_flags())//<>
			return (0);
		else if ((s[i] == '>' && !check_flags()) || (s[i] == '<' && !check_flags()))
		{
			if (s[i + 1] == '>' || s[i + 1] == '<')
				i += 2;
			else
				i++;
			while (s[i] == ' ')
				i++;
			if (ft_strchr("<>|", s[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_syntax(char *s)
{
	if (g_msh.pipe_count > 1)
	{
		if (!check_pipe(s))
		{
			free(s);
			return (error_func(ERR_SYNTAX, 0, 1, "|\n"));
		}
	}
	if (s[ft_strlen(s) - 1] == '\\')
	{
		free(s);
		return (error_func(ERR_SYNTAX, 0, 1, "\\\n"));
	}
	if (!check_sq(s))
	{
		free(s);
		return (error_func(ERR_SYNTAX, 0, 1, "\'\n"));
	}
	if (!check_wq(s))
	{
		free(s);
		return (error_func(ERR_SYNTAX, 0, 1, "\"\n"));
	}
	if (!check_rd(s))
	{
		free(s);
		return (error_func(ERR_SYNTAX, 0, 1, "> or <\n"));
	}
	return (1);
}

// int	check_empty(char *s)
// {
// 	char	*tmp;

// 	tmp = ft_strdup(s);
// 	if (tmp == NULL)
// 		error_func(ERROR_MEM, 1, 0, NULL);
// 	tmp = del_start_sp(tmp);
// 	tmp = del_end_sp(tmp);
// 	if (!ft_strlen(tmp))
// 	{
// 		free(tmp);
// 		return (1);
// 	}
// 	free(tmp);
// 	return (0);
// }