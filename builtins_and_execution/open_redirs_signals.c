#include "minishell.h"

void	sig_handler_promt_rd(int signum)
{
	if (signum == SIGINT)
		g_msh.rdfl = 1;
	else if (signum == SIGQUIT)
		return ;
}

void	wait4signal_rd(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, sig_handler_promt_rd);
}
