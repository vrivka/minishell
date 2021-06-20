#include "minishell.h"

int	key_decisions_rd(char *buf, int c, int len)
{
	if (len == -1)
		error_func(ERR_READKEY, 1, 0, NULL);
	else if (!ft_strcmp(buf, "\e[D"))
		key_left_func_rd();
	else if (!ft_strcmp(buf, "\e[C"))
		key_right_func_rd();
	else if (!ft_strcmp(buf, "\177"))
		key_bs_func_rd();
	else if (!ft_strcmp(buf, "\n"))
		return (2);
	else if (!ft_strcmp(buf, "\4") && !ft_strlen(g_msh.line))
		return (0);
	else if (!ft_strcmp(buf, "\3"))
	{
		key_ctrlc_func_rd();
		return (0);
	}
	else
	{
		if (ft_isprint(buf[0]) && ft_strcmp(buf, "\t"))
			key_print_func_rd(buf, c, len);
	}
	return (1);
}

int	key_loop_rd(void)
{
	char	buf[BUFFER_SIZE];
	int		len;
	int		ret;

	g_msh.rdfl = 0;
	wait4signal_rd();
	while (1)
	{
		ft_memset(buf, 0, BUFFER_SIZE);
		len = read(0, buf, BUFFER_SIZE);
		ret = key_decisions_rd(buf, (int)(buf[0]), len);
		if (!ret)
			return (0);
		else if (ret == 2)
			break ;
		else if (ret == 1)
			continue ;
	}
	return (1);
}
