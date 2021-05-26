/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:07:23 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/24 13:32:30 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordlen(const char *s, char c, int i)
{
	int	wl;

	wl = 0;
	while (s[i] != c && s[i] != '\0')
	{
		wl++;
		i++;
	}
	return (wl);
}

static int	wordcount(const char *s, char c)
{
	int	i;
	int	wc;
	int	sl;

	sl = ft_strlen(s);
	i = 0;
	wc = 0;
	while (i < sl)
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			wc++;
		}
		i++;
	}
	return (wc);
}

static int	splitmain(char const *s, char *arr, char c, int i)
{
	int	i1;

	i1 = 0;
	while (s[i] != c && s[i] != '\0')
	{
		arr[i1] = s[i];
		i1++;
		i++;
	}
	arr[i1] = '\0';
	return (i);
}

static char	*mallocarr(char **arr, int f, int i)
{
	if (!(arr[i] = (char *)malloc(sizeof(char) * (f + 1))))
	{
		i--;
		while (i >= 0)
		{
			free(arr[i]);
			i--;
		}
		free(arr);
		return (NULL);
	}
	return (arr[i]);
}

char		**ft_split(char const *s, char c)
{
	char	**arr;
	int		i[4];

	i[0] = 0;
	i[1] = 0;
	if (s == NULL)
		return (NULL);
	i[2] = wordcount(s, c);
	if (!(arr = (char **)malloc(sizeof(char *) * (i[2] + 1))))
		return (NULL);
	while (i[2] > 0)
	{
		i[3] = wordlen(s, c, i[1]);
		if (i[3] != 0)
		{
			if (!(arr[i[0]] = mallocarr(arr, i[3], i[0])))
				return (NULL);
			i[1] = splitmain(s, arr[i[0]], c, i[1]);
			i[0]++;
			i[2]--;
		}
		i[1]++;
	}
	arr[i[0]] = NULL;
	return (arr);
}
