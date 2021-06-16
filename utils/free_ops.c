#include "minishell.h"

void	free_d_arr(char **array)
{
	int	j;

	j = 0;
	while (array[j] != NULL)
	{
		if (array[j])
		{
			free(array[j]);
			array[j] = NULL;
		}
		j++;
	}
	if (array)
	{
		free(array);
		array = NULL;
	}
}

void	free_pipe(void)
{
	int	i;

	i = 0;
	while (i < g_msh.pipe_count)
	{
		if (g_msh.pipe[i].args != NULL)
		{
			free_d_arr(g_msh.pipe[i].args);
			g_msh.pipe[i].args = NULL;
		}
		if (g_msh.pipe[i].rd != NULL)
		{
			free_d_arr(g_msh.pipe[i].rd);
			g_msh.pipe[i].rd = NULL;
		}
		if (g_msh.pipe[i].bin_path != NULL)
			free(g_msh.pipe[i].bin_path);
		i++;
	}
	if (g_msh.pipe != NULL)
	{
		free(g_msh.pipe);
		g_msh.pipe = NULL;
	}
}
