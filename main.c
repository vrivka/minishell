#include "minishell.h"

void	main_loop(void)
{
	g_msh.line = ft_strnew(0);
	reinit_history();
	g_msh.pos = 0;
	unset_term();
	key_loop();
	write(1, "\n", 1);
	set_term();
	clean_line();
	if (ft_strlen(g_msh.line) == 0)
	{
		free(g_msh.line);
		return ;
	}
	else
	{
		semicolon_splitter();
		if (!check_semi())
		{
			free_d_arr(g_msh.semi);
			error_func(ERR_SYNTAX, 0, 1, ";\n");
			return ;
		}
		launch();
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	init_msh(av, envp);
	term_setup();
	while (1)
		main_loop();
	return (0);
}
