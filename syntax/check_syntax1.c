#include "minishell.h"

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
		if ((s[i] == '>' && !check_flags()) || \
		(s[i] == '<' && !check_flags()))
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

int	check_drd(char *s)
{
	int	i;

	g_msh.flags = NOFLG;
	i = 0;
	while (s[i])
	{
		set_flags(s[i]);
		if (s[i] == '>' && s[i + 1] == '<' && !check_flags())
			return (0);
		else if (s[i] == '<' && s[i + 1] == '>' && !check_flags())
			return (0);
		i++;
	}
	return (1);
}

int	check_syntax(char *s)
{
	if (g_msh.pipe_count > 1)
	{
		if (!check_pipe(s))
			return (error_func(ERR_SYNTAX, 0, 1, "|\n"));
	}
	if (s[ft_strlen(s) - 1] == '\\')
		return (error_func(ERR_SYNTAX, 0, 1, "\\\n"));
	if (!check_sq(s))
		return (error_func(ERR_SYNTAX, 0, 1, "\'\n"));
	if (!check_wq(s))
		return (error_func(ERR_SYNTAX, 0, 1, "\"\n"));
	if (!check_rd(s) || !check_drd(s))
		return (error_func(ERR_SYNTAX, 0, 1, "> or <\n"));
	return (1);
}
