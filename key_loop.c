#include "minishell.h"

void	key_loop(void)
{
	char	buf[BUFFER_SIZE];
	int		len;

	while (1)
	{
		ft_memset(buf, 0, BUFFER_SIZE);
		len = read(0, buf, BUFFER_SIZE);
		if (len == -1)
			error_func(ERR_READKEY, 1, 0, NULL);
		if (!ft_strcmp(buf, "\e[A"))//up
		{
			if (g_msh.h_index >= 0)
			{
				g_msh.pos = 0;
				if (g_msh.h_index > 0)
					g_msh.h_index--;
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tgetstr("ce", 0), 1, ft_putchar);
				write(1, g_msh.history[g_msh.h_index], ft_strlen(g_msh.history[g_msh.h_index]));
				g_msh.pos += ft_strlen(g_msh.history[g_msh.h_index]);
			}
		}
		else if (!ft_strcmp(buf, "\e[B"))//down
		{
			if (g_msh.h_index < g_msh.h_size)
			{
				g_msh.pos = 0;
				if (g_msh.h_index < (g_msh.h_size - 1))
					g_msh.h_index++;
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tgetstr("ce", 0), 1, ft_putchar);
				write(1, g_msh.history[g_msh.h_index], ft_strlen(g_msh.history[g_msh.h_index]));
				g_msh.pos += ft_strlen(g_msh.history[g_msh.h_index]);
			}
		}
		else if (!ft_strcmp(buf, "\177"))//backspace
		{
			if (g_msh.pos > 0)
			{
				g_msh.history[g_msh.h_index] = ft_del_chinstr(g_msh.history[g_msh.h_index], g_msh.pos);
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
				g_msh.pos--;
			}
		}
		else if (!ft_strcmp(buf, "\t"))//tab
			continue ;
		else if (!ft_strcmp(buf, "\n"))//enter
		{
			g_msh.history[g_msh.h_size - 1] = ft_strrewrite(g_msh.history[g_msh.h_size - 1], g_msh.history[g_msh.h_index]);
			g_msh.line = ft_strrewrite(g_msh.line, g_msh.history[g_msh.h_size - 1]);
			g_msh.pos = 0;
			break;
		}
		else if (!ft_strcmp(buf, "\e[D"))//left
		{
			if (g_msh.pos > 0)
			{
				tputs(tgetstr("le", 0), 1, ft_putchar);
				g_msh.pos--;
			}
		}
		else if (!ft_strcmp(buf, "\e[C"))//right
		{
			if (g_msh.pos < ft_strlen(g_msh.history[g_msh.h_index]))
			{
				tputs(tgetstr("nd", 0), 1, ft_putchar);
				g_msh.pos++;
			}
		}
		else
		{
			if (ft_isprint(buf[0]))//print
			{
				tputs(tgetstr("im", 0), 1, ft_putchar);
				g_msh.history[g_msh.h_index] = ft_ins_ch2str(g_msh.history[g_msh.h_index], buf[0], g_msh.pos);
				g_msh.pos++;
				write (1, buf, len);
				tputs(tgetstr("ei", 0), 1, ft_putchar);
			}
		}
	}
}
