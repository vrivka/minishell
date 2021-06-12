#include "minishell.h"

void	free_d_arr(char **array)
{
	int	j;

	j = 0;
	while (array[j] != NULL)
	{
		if (array[j])
			free(array[j]);
		j++;
	}
	if (array)
		free(array);
}

void	free_pipe(void)
{
	int	i;

	i = 0;
	while(i < g_msh.pipe_count)
	{
		free_d_arr(g_msh.pipe[i].args);
		free_d_arr(g_msh.pipe[i].rd);
		free(g_msh.pipe[i].bin_path);
		i++;
	}
	free(g_msh.pipe);
}
