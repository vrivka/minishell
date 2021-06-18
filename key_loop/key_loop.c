#include "minishell.h"

void	wait4signals(void)
{
	signal(SIGINT, sig_handler_promt);
	signal(SIGQUIT, sig_handler_promt);
}

void	welcome_promt(void)
{
	write(1, "msh$ ", 5);
	tputs(save_cursor, 1, ft_putchar);
}

int	key_decisions(char *buf, int c, int len)
{
	if (!ft_strcmp(buf, "\e[A"))
		key_up_func();
	else if (!ft_strcmp(buf, "\e[B"))
		key_down_func();
	else if (!ft_strcmp(buf, "\e[D"))
		key_left_func();
	else if (!ft_strcmp(buf, "\e[C"))
		key_right_func();
	else if (!ft_strcmp(buf, "\177"))
		key_bs_func();
	else if (!ft_strcmp(buf, "\n"))
	{
		if (!key_enter_func())
			return (0);
	}
	else if (!ft_strcmp(buf, "\4"))
		key_ctrld_func();
	else
	{
		if (ft_isprint(buf[0]) && ft_strcmp(buf, "\t"))
			key_print_func(buf, c, len);
	}
	return (1);
}

void	key_loop(void)
{
	char	buf[BUFFER_SIZE];
	int		len;

	wait4signals();
	welcome_promt();
	while (1)
	{
		ft_memset(buf, 0, BUFFER_SIZE);
		len = read(0, buf, BUFFER_SIZE);
		if (len == -1)
			error_func(ERR_READKEY, 1, 0, NULL);
		if (!key_decisions(buf, (int)(buf[0]), len))
			break ;
	}
}
