#include "minishell.h"

char	*ft_cutstr_begin(char *s1, int i)
{
	char	*s2;
	int		len;
	int		j;

	len = ft_strlen(s1);
	s2 = (char *)ft_calloc(sizeof(char), (len - i + 1));
	if (s2 == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	j = 0;
	while (s1[i] != '\0')
	{
		s2[j] = s1[i];
		i++;
		j++;
	}
	free(s1);
	return (s2);
}

char	*ft_cutstr_end(char *s, int pos)
{
	char	*tmp;
	int		i;

	tmp = (char *)ft_calloc(sizeof(char), (pos + 1));
	if (tmp == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	i = 0;
	while (i < pos)
	{
		tmp[i] = s[i];
		i++;
	}
	free(s);
	return (tmp);
}

char	*ft_add_char2str(char *s, int c)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(s);
	new = (char *)ft_calloc(sizeof(char), (len + 2));
	if (new == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = c;
	free(s);
	return (new);
}

char	*ft_ins_ch2str(char *s, int c, int pos)
{
	char	**arr;
	char	*tmp;

	arr = ft_devide_str(s, pos);
	arr[0] = ft_add_char2str(arr[0], c);
	tmp = ft_strjoin(arr[0], arr[1]);
	free_d_arr(arr);
	free(s);
	return (tmp);
}
