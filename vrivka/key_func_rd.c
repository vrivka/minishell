#include "minishell.h"

void	key_bs_func_rd(void)
{
	if (g_msh.pos > 0)
	{
		g_msh.line = ft_del_chinstr(g_msh.line, g_msh.pos);
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		g_msh.pos--;
	}
}

void	key_left_func_rd(void)
{
	if (g_msh.pos > 0)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		g_msh.pos--;
	}
}

void	key_right_func_rd(void)
{
	if (g_msh.pos < ft_strlen(g_msh.line))
	{
		tputs(tgetstr("nd", 0), 1, ft_putchar);
		g_msh.pos++;
	}
}

void	key_print_func_rd(char *buf, int c, int len)
{
	tputs(tgetstr("im", 0), 1, ft_putchar);
	g_msh.line = ft_ins_ch2str(g_msh.line, c, g_msh.pos);
	g_msh.pos++;
	write (1, buf, len);
	tputs(tgetstr("ei", 0), 1, ft_putchar);
}

void	key_ctrlc_func_rd(void)
{
	g_msh.rdfl = 1;
	write(1, "\n", 1);
}
