#include "minishell.h"

char	*ft_strnew(size_t n)
{
	char	*str;

	str = (char *)ft_calloc((n + 1), sizeof(char));
	if (str == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	return (str);
}

char	*ft_strjoin_fr(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	s[i] = '\0';
	free(s1);
	return (s);
}

char	*ft_strdellstch_fr(char *s1)
{
	char	*s;
	int		i;
	int		len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	s = (char *)ft_calloc(sizeof(char), len);
	if (s == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	while (i < (len - 1))
	{
		s[i] = s1[i];
		i++;
	}
	free(s1);
	return (s);
}

char	*ft_strrewrite(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s2);
	s = (char *)ft_calloc(sizeof(char), (len + 1));
	if (s == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	while (i < len)
	{
		s[i] = s2[i];
		i++;
	}
	free(s1);
	return (s);
}

char	*ft_del_chinstr(char *s, int pos)
{
	char	**arr;
	char	*tmp;

	arr = ft_devide_str(s, pos);
	arr[0] = ft_strdellstch_fr(arr[0]);
	tmp = ft_strjoin(arr[0], arr[1]);
	free_d_arr(arr);
	free(s);
	return (tmp);
}
