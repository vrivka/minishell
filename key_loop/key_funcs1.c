#include "minishell.h"

void	key_up_func(void)
{
	int	len;

	if (g_msh.h_index >= 0)
	{
		g_msh.pos = 0;
		if (g_msh.h_index > 0)
			g_msh.h_index--;
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		len = ft_strlen(g_msh.history[g_msh.h_index]);
		write(1, g_msh.history[g_msh.h_index], len);
		g_msh.pos += ft_strlen(g_msh.history[g_msh.h_index]);
	}
}

void	key_down_func(void)
{
	int	len;

	if (g_msh.h_index < g_msh.h_size)
	{
		g_msh.pos = 0;
		if (g_msh.h_index < (g_msh.h_size - 1))
			g_msh.h_index++;
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		len = ft_strlen(g_msh.history[g_msh.h_index]);
		write(1, g_msh.history[g_msh.h_index], len);
		g_msh.pos += ft_strlen(g_msh.history[g_msh.h_index]);
	}
}

void	key_left_func(void)
{
	if (g_msh.pos > 0)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		g_msh.pos--;
	}
}

void	key_right_func(void)
{
	if (g_msh.pos < ft_strlen(g_msh.history[g_msh.h_index]))
	{
		tputs(tgetstr("nd", 0), 1, ft_putchar);
		g_msh.pos++;
	}
}
