/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:58:47 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/24 11:59:34 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	charcountf(char const *s1, char const *set)
{
	int	i1;
	int	i2;
	int	c;

	i1 = 0;
	i2 = 0;
	c = ft_strlen(set);
	while (s1[i1] != '\0')
	{
		while (set[i2] != '\0')
		{
			if (s1[i1] == set[i2])
				break ;
			else
				i2++;
		}
		if (i2 == c)
			return (i1);
		i2 = 0;
		i1++;
	}
	return (i1);
}

static int	charcountb(char const *s1, char const *set)
{
	int	i1;
	int	i2;
	int	c;

	i1 = ft_strlen(s1) - 1;
	i2 = 0;
	c = ft_strlen(set);
	while (i1 >= 0)
	{
		while (set[i2] != '\0')
		{
			if (s1[i1] == set[i2])
				break ;
			else
				i2++;
		}
		if (i2 == c)
			return (i1);
		i2 = 0;
		i1--;
	}
	return (i1);
}

static char	*strtrimmain(char const *s1, int i1, int i2)
{
	char	*s;
	int		i;

	i = 0;
	if (!(s = (char *)malloc(sizeof(char) * ((i2 - i1 + 1) + 1))))
		return (NULL);
	while (i1 <= i2)
	{
		s[i] = s1[i1];
		i++;
		i1++;
	}
	s[i] = '\0';
	return (s);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		i1;
	int		i2;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i1 = charcountf(s1, set);
	i2 = charcountb(s1, set);
	if (i1 <= i2)
		return (strtrimmain(s1, i1, i2));
	else
	{
		if (!(s = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
		s[0] = '\0';
	}
	return (s);
}
