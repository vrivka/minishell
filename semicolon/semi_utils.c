#include "minishell.h"

void	set_flags(int c)
{
	if ((g_msh.flags & BSFLG) && (g_msh.flags & UBSFL))
	{
		g_msh.flags = g_msh.flags & (~UBSFL);
		g_msh.flags = g_msh.flags & (~BSFLG);
	}
	if (c == '\'' && !(g_msh.flags & SQFLG) && !(g_msh.flags & BSFLG))
		g_msh.flags = g_msh.flags | SQFLG;
	else if (c == '\'' && (g_msh.flags & SQFLG) && !(g_msh.flags & BSFLG))
		g_msh.flags = g_msh.flags & (~SQFLG);
	else if (c == '\"' && \
	!(g_msh.flags & SQFLG) && !(g_msh.flags & BSFLG) && !(g_msh.flags & WQFLG))
		g_msh.flags = g_msh.flags | WQFLG;
	else if (c == '\"' && \
	!(g_msh.flags & SQFLG) && !(g_msh.flags & BSFLG) && (g_msh.flags & WQFLG))
		g_msh.flags = g_msh.flags & (~WQFLG);
	else if (c == '\\' && !(g_msh.flags & SQFLG) && !(g_msh.flags & BSFLG))
		g_msh.flags = g_msh.flags | BSFLG;
	else if ((g_msh.flags & BSFLG) && !(g_msh.flags & UBSFL))
		g_msh.flags = g_msh.flags | UBSFL;
}

int	check_flags(void)
{
	if ((g_msh.flags & SQFLG) || (g_msh.flags & WQFLG) || (g_msh.flags & BSFLG))
		return (1);
	else
		return (0);
}
