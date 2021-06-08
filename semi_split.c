#include "minishell.h"

void	set_flags(int c)
{
	if (c == '\'' && !(g_msh.flags & SQFLG) && !(g_msh.flags & BSFLG))
		g_msh.flags = g_msh.flags | SQFLG;
	else if (c == '\'' && (g_msh.flags & SQFLG) && !(g_msh.flags & BSFLG))
		g_msh.flags = g_msh.flags & (~SQFLG);
	else if (c == '\"' && !(g_msh.flags & SQFLG) && !(g_msh.flags & BSFLG) && !(g_msh.flags & WQFLG))
		g_msh.flags = g_msh.flags | WQFLG;
	else if (c == '\"' && !(g_msh.flags & SQFLG) && !(g_msh.flags & BSFLG) && (g_msh.flags & WQFLG))
		g_msh.flags = g_msh.flags & (~WQFLG);
	else if (c == '\\' && !(g_msh.flags & SQFLG) && !(g_msh.flags & BSFLG))
		g_msh.flags = g_msh.flags | BSFLG;
	else if ((g_msh.flags & BSFLG) && !(g_msh.flags & UBSFL))
		g_msh.flags = g_msh.flags | UBSFL;
	else if ((g_msh.flags & BSFLG) && (g_msh.flags & UBSFL))
	{
		g_msh.flags = g_msh.flags & (~UBSFL);
		g_msh.flags = g_msh.flags & (~BSFLG);
	}
}

int		check_flags(void)
{
	if ((g_msh.flags & SQFLG) || (g_msh.flags & WQFLG) || (g_msh.flags & BSFLG))
		return (1);
	else
		return (0);
}

int		get_semi_num(char *s)//count num of semicolons to devide line
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	g_msh.flags = NOFLG;
	while (s[i])
	{
		set_flags(s[i]);
		if (s[i] == ';' && !check_flags())
			n++;
		i++;
	}
	return (n);
}

int		get_semiline_len(char *s)
{
	int	len;

	g_msh.flags = NOFLG;
	len = 0;
	while (s[g_msh.pos])
	{
		set_flags(s[g_msh.pos]);
		if (s[g_msh.pos] == ';' && !check_flags())
			break ;
		g_msh.pos++;
		len++;
	}
	return (len);
}

void	init_semicolon_array(void)//need to free semi array
{
	int	len;
	int	n;
	g_msh.pos = 0;//may be it`s unnecessary))

	g_msh.semi_count = get_semi_num(g_msh.line) + 1;
	// printf("count: %d\n", g_msh.semi_count);//
	g_msh.semi = (char **)ft_calloc(sizeof(char *), (g_msh.semi_count + 1));//if ==NULL
	n = 0;
	while(n < g_msh.semi_count)
	{
		len = get_semiline_len(g_msh.line);
		// printf("len: %d\n", len);//
		g_msh.semi[n] = (char *)ft_calloc(sizeof(char), (len + 1));
		if (g_msh.line[g_msh.pos] == ';')
			g_msh.pos++;
		n++;
	}
}

void	fill_semicolon_array(void)
{
	int	n;
	int	i;

	g_msh.pos = 0;
	n = 0;
	i = 0;
	while (g_msh.line[g_msh.pos])
	{
		if (g_msh.line[g_msh.pos] == ';')
		{
			g_msh.pos++;
			n++;
			i = 0;
			continue;
		}
		g_msh.semi[n][i] = g_msh.line[g_msh.pos];
		g_msh.pos++;
		i++;
	}
}

void	semicolon_splitter(void)
{
	// printf("line: %s\n", g_msh.line);//
	init_semicolon_array();
	fill_semicolon_array();
	free(g_msh.line);

	// /// print test
	// int i = 0;
	// while (g_msh.semi[i])
	// {
	// 	printf("semi[%d]# %s\n", i, g_msh.semi[i]);
	// 	i++;
	// }
	// ///
}