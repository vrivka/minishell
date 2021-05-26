/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:28:44 by epilar            #+#    #+#             */
/*   Updated: 2020/11/10 12:26:05 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	clear_mem(char **str, int i)
{
	i--;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
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

char		**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		start;
	int		len;

	if (s == NULL)
		return (NULL);
	if (!(str = (char **)ft_calloc(sizeof(char *), (num_of_str(s, c) + 1))))
		return (NULL);
	i = 0;
	start = 0;
	len = 0;
	while (i < num_of_str(s, c))
	{
		find_word(s, c, &start, &len);
		if (!(str[i] = (char *)malloc(sizeof(char) * (len + 1))))
		{
			clear_mem(str, i);
			return (NULL);
		}
		ft_strlcpy(str[i], &s[start], len + 1);
		i++;
	}
	return (str);
}
