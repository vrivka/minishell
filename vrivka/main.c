#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;

	all_init(env);
	cd_func(av);
	all_free();
//	while (1) {}
}
