#include "minishell.h"

char	**ft_devide_str(char *s, int pos)
{
	char	**arr;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(s);
	arr = (char **)ft_calloc(sizeof(char *), 3);
	if (arr == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	arr[0] = (char *)ft_calloc(sizeof(char), (pos + 1));
	if (arr[0] == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	arr[1] = (char *)ft_calloc(sizeof(char), (len - pos + 1));
	if (arr[1] == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	i = 0;
	j = 0;
	while (i < pos)
		arr[0][j++] = s[i++];
	j = 0;
	while (i < len)
		arr[1][j++] = s[i++];
	return (arr);
}

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
