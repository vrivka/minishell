#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_msh.history[g_msh.h_size - 1] = ft_strrewrite(g_msh.history[g_msh.h_size - 1], "");
		write(1, "\n", 1);
		write(1, "msh$ ", 5);
		g_msh.pos = 0;
	}
	else if (signum == SIGQUIT)
		write(1, "QUIT: 3\n", 8);
		return ;
}
