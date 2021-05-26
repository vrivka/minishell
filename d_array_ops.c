#include "minishell.h"

char	**add_str2darr(char **arr)
{
	char	**new;
	int		size;
	int		j;

	size = count_arr_lines(arr);
	new = (char **)ft_calloc(sizeof(char *), (size + 2));//if new = NULL
	j = 0;
	while (arr[j] != NULL)
	{
		new[j] = (char *)ft_calloc(sizeof(char), 1);//if new[j] = NULL
		new[j] = ft_strrewrite(new[j], arr[j]);
		j++;
	}
	new[j] = (char *)ft_calloc(sizeof(char), 1);//if new[j] = NULL
	free_d_arr(arr);
	return (new);
}