#include "minishell.h"

void	reinit_history(void)
{
	g_msh.history = add_str2darr(g_msh.history);
	g_msh.h_size = count_arr_lines(g_msh.history);
	g_msh.h_index = g_msh.h_size - 1;
}

int	count_arr_lines(char **array)
{
	int	count;

	count = 0;
	while (array[count] != NULL)
		count++;
	return (count);
}

void	unset_term(void)
{
	int	ret;

	g_msh.term->c_lflag &= ~(ECHO);
	g_msh.term->c_lflag &= ~(ICANON);
	ret = tcsetattr(0, TCSANOW, g_msh.term);
	if (ret == -1)
		error_func(ERR_SETTERM, 1, 0, NULL);
}

void	set_term(void)
{
	int	ret;

	g_msh.term->c_lflag |= ECHO;
	g_msh.term->c_lflag |= ICANON;
	ret = tcsetattr(0, TCSANOW, g_msh.term);
	if (ret == -1)
		error_func(ERR_SETTERM, 1, 0, NULL);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}
