#include "minishell.h"

char	**add_str2darr(char **arr)
{
	char	**new;
	int		size;
	int		j;

	size = count_arr_lines(arr);
	new = (char **)ft_calloc(sizeof(char *), (size + 2));
	if (new == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	j = 0;
	while (arr[j] != NULL)
	{
		new[j] = ft_strnew(0);
		new[j] = ft_strrewrite(new[j], arr[j]);
		j++;
	}
	new[j] = ft_strnew(0);
	free_d_arr(arr);
	return (new);
}

char	**ins_str2arr(char **arr, int n)
{
	char	**new;
	int		size;
	int		j;
	int		k;

	size = count_arr_lines(arr);
	new = (char **)ft_calloc((size + 1 + 1), sizeof(char **));
	if (new == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	j = 0;
	k = 0;
	while (arr[j] != NULL)
	{
		new[k] = ft_strnew(0);
		new[k] = ft_strrewrite(new[k], arr[j]);
		if (j == n)
		{
			k++;
			new[k] = ft_strnew(0);
		}
		j++;
		k++;
	}
	free_d_arr(arr);
	return (new);
}
