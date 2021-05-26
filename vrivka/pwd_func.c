#include "minishell.h"

int pwd_func(void)
{
	g_msh.pwd = getcwd(g_msh.pwd, 0);
	printf("%s\n", g_msh.pwd);
	free(g_msh.pwd);
	g_msh.pwd = NULL;
	return(0);
}
