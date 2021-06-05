#include "libft.h"

static int	num_of_str(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
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

static void	find_word(char const *s, char c, int *start, int *len)
{
	*start = *start + *len;
	*len = 0;
	while (s[*start] == c)
		(*start)++;
	while (s[*start + *len] != c && s[*start + *len] != '\0')
		(*len)++;
}

static void	fill_array(char **arr, char *s, char c)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	while (i < num_of_str(s, c))
	{
		find_word(s, c, &start, &len);
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

char	**ft_split(char const *s, char c)
{
	char	**arr;

	arr = NULL;
	if (s == NULL)
		return (NULL);
	arr = (char **)ft_calloc(sizeof(char *), (num_of_str(s, c) + 1));
	if (arr == NULL)
		return (NULL);
	fill_array(arr, (char *)s, c);
	return (arr);
}
