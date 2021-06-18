#include "minishell.h"

void	key_bs_func(void)
{
	if (g_msh.pos > 0)
	{
		g_msh.history[g_msh.h_index] = \
		ft_del_chinstr(g_msh.history[g_msh.h_index], g_msh.pos);
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		g_msh.pos--;
	}
}

void	key_ctrld_func(void)
{
	if (!ft_strlen(g_msh.history[g_msh.h_index]))
	{
		write(1, "exit\n", 5);
		put_hist2file();
		set_term();
		free(g_msh.term);
		exit(0);
	}
}

void	key_print_func(char *buf, int c, int len)
{
	tputs(tgetstr("im", 0), 1, ft_putchar);
	g_msh.history[g_msh.h_index] = \
	ft_ins_ch2str(g_msh.history[g_msh.h_index], c, g_msh.pos);
	g_msh.pos++;
	write (1, buf, len);
	tputs(tgetstr("ei", 0), 1, ft_putchar);
}

int	key_enter_func(void)
{
	if (ft_strlen(g_msh.history[g_msh.h_index]) == 0)
	{
		g_msh.h_index = g_msh.h_size - 1;
		g_msh.history[g_msh.h_index] = \
		ft_strrewrite(g_msh.history[g_msh.h_index], "");
		write(1, "\n", 1);
		welcome_promt();
		return (1);
	}
	else
	{
		g_msh.history[g_msh.h_size - 1] = \
		ft_strrewrite(g_msh.history[g_msh.h_size - 1], \
		g_msh.history[g_msh.h_index]);
		g_msh.line = ft_strrewrite(g_msh.line, g_msh.history[g_msh.h_size - 1]);
		g_msh.pos = 0;
		return (0);
	}
}
