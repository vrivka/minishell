/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:07:04 by epilar            #+#    #+#             */
/*   Updated: 2020/11/08 12:30:52 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int		in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char					*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	unsigned int	size;
	char			*start;
	char			*end;
	char			*trim;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && in_set(s1[i], set))
		i++;
	start = (char *)&s1[i];
	if ((i = ft_strlen((char *)s1) - 1) != -1)
		while (i >= 0 && in_set(s1[i], set))
			i--;
	end = (char *)&s1[i];
	if (!*s1 || end == start)
		size = 2;
	else
		size = end - start + 2;
	if (!(trim = malloc(sizeof(char) * size)))
		return (NULL);
	ft_strlcpy(trim, start, size);
	return (trim);
}
