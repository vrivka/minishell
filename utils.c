#include "minishell.h"

void	repair_empty_rd(void)
{
	int	i;
	int	n;

	i = 0;
	while(i < g_msh.pipe_count)
	{
		n = 0;
		while(g_msh.pipe[i].rd[n] != NULL)
		{
			if ((!ft_strcmp("<", g_msh.pipe[i].rd[n]) || !ft_strcmp(">", g_msh.pipe[i].rd[n]) || \
			!ft_strcmp("<<", g_msh.pipe[i].rd[n]) || !ft_strcmp(">>", g_msh.pipe[i].rd[n])) && \
			(!ft_strcmp("<", g_msh.pipe[i].rd[n + 1]) || !ft_strcmp(">", g_msh.pipe[i].rd[n + 1]) || \
			!ft_strcmp("<<", g_msh.pipe[i].rd[n + 1]) || !ft_strcmp(">>", g_msh.pipe[i].rd[n + 1])))
			{
				g_msh.pipe[i].rd = ins_str2arr(g_msh.pipe[i].rd, n);
				continue;
			}
			n++;
		}
		i++;
	}
}

int		count_arr_lines(char **array)
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

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}	
