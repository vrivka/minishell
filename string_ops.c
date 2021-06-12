#include "minishell.h"

char	*ft_strnew(size_t n)
{
	char	*str;

	str = (char *)ft_calloc((n + 1), sizeof(char));//if ==NULL
	if (str == NULL)
		exit(0);
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
	if (!(s = (char *)malloc(sizeof(char) * (ft_strlen(s1) +
				ft_strlen(s2) + 1))))
		return (NULL);
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

char *ft_strdellstch_fr(char *s1)
{
	char	*s;
	int		i;
	int		len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (!(s = (char *)ft_calloc(sizeof(char), len)))
		return (NULL);
	while (i < (len - 1))
	{
		s[i] = s1[i];
		i++;
	}
	free(s1);
	return (s);
}

char	*ft_strrewrite(char *s1, char *s2)//target/source
{
	char	*s;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s2);
	s = (char *)ft_calloc(sizeof(char), (len + 1));
	while (i < len)
	{
		s[i] = s2[i];
		i++;
	}
	free(s1);
	return (s);
}

char	*ft_cutstr_begin(char *s1, int i)
{
	char	*s2;
	int		len;
	int		j;

	len = ft_strlen(s1);
	s2 = (char *)ft_calloc(sizeof(char), (len - i + 1));//if s2 = NULL
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

	tmp = (char *)ft_calloc(sizeof(char), (pos + 1));//if tmp == NULL
	if (tmp == NULL)
		exit(0);
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
	new = (char *)ft_calloc(sizeof(char), (len + 2));//if new = NULL
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

char	**ft_devide_str(char *s, int pos)
{
	char	**arr;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(s);
	arr = (char **)ft_calloc(sizeof(char *), 3);
	arr[0] = (char *)ft_calloc(sizeof(char), (pos + 1));
	arr[1] = (char *)ft_calloc(sizeof(char), (len - pos  + 1));
	i = 0;
	j = 0;
	while (i < pos)
	{
		arr[0][j] = s[i];
		i++;
		j++;
	}
	j = 0;
	while (i < len)
	{
		arr[1][j] = s[i];
		i++;
		j++;
	}
	return (arr);
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

//sp flag
void	change_sp2us(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while ((*s)[i] != '\0')
		{
			if ((*s)[i] == ' ')
				(*s)[i] = '_';
			i++;
		}
	}
	else
		return ;
}
//

char	*del_start_sp(char *s1)
{
	char	*s2;
	int		i;

	s2 = NULL;
	i = 0;
	if (s1[i] == ' ')
	{
		while (s1[i] == ' ')
			i++;
		s2 = ft_cutstr_begin(s1, i);
		return (s2);
	}
	return (s1);
}

char	*del_end_sp(char *s1)
{
	char	*s2;
	int		i;
	int		len;

	s2 = NULL;
	len = ft_strlen(s1);
	i = len - 1;
	if (s1[i] == ' ')
	{
		while (s1[i] == ' ')
			i--;
		s2 = ft_cutstr_end(s1, (i + 1));
		return (s2);
	}
	return (s1);
}