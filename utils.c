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
