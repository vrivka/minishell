#include "minishell.h"

static int	num_of_str(char const *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && (s[i + 1] == ' ' || s[i + 1] == '\0') && \
		(g_msh.check_sprds[i + 1] == ' ' || g_msh.check_sprds[i + 1] == '\0'))
			count++;
		if (s[i] == ' ' && g_msh.check_sprds[i] == '_' && (s[i + 1] == ' ' || \
		s[i + 1] == '\0') && (g_msh.check_sprds[i + 1] == ' ' || \
		g_msh.check_sprds[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	clear_mem(char **str)
{
	int	j;

	j = 0;
	while (str[j] != NULL)
	{
		free(str[j]);
		str[j] = NULL;
		j++;
	}
	free(str);
	str = NULL;
}

static void	find_word(char const *s, int *start, int *len)
{
	*start = *start + *len;
	*len = 0;
	while (s[*start] == ' ')
	{
		if (g_msh.check_sprds[*start] == '_')
			break ;
		(*start)++;
	}
	while (g_msh.check_sprds[*start + *len] != ' ' && \
	g_msh.check_sprds[*start + *len] != '\0')
		(*len)++;
}

static void	fill_arr(char **arr, char *s)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	while (i < num_of_str(s))
	{
		find_word(s, &start, &len);
		arr[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (arr[i] == NULL)
		{
			clear_mem(arr);
			break ;
		}
		ft_strlcpy(arr[i], &s[start], len + 1);
		i++;
	}
}

char	**ft_sprds_split(char const *s)
{
	char	**arr;

	arr = NULL;
	if (s == NULL)
		return (NULL);
	arr = (char **)ft_calloc(sizeof(char *), (num_of_str(s) + 1));
	if (arr == NULL)
		return (NULL);
	fill_arr(arr, (char *)s);
	return (arr);
}
