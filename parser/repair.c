#include "minishell.h"

void	repair_empty_args(int i)
{
	if (g_msh.pipe[i].args[0] == NULL)
	{
		g_msh.pipe[i].args[0] = ft_strrewrite(g_msh.pipe[i].args[0], "");
		g_msh.pipe[i].args[1] = NULL;
	}
}

void	repair_empty_rd(int i)
{
	int	n;

	n = 0;
	while (g_msh.pipe[i].rd[n] != NULL)
	{
		if (check_alone_rd(i, n))
		{
			g_msh.pipe[i].rd = ins_str2arr(g_msh.pipe[i].rd, n);
			continue ;
		}
		n++;
	}
}
