/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:52:34 by epilar            #+#    #+#             */
/*   Updated: 2020/11/08 12:17:30 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[i] != '\0' && i < n)
	{
		j = 0;
		while (s1[i] == s2[j] && i < n && s1[i] != '\0' && s2[j] != '\0')
		{
			i++;
			j++;
		}
		if (s2[j] == '\0' && i - j < n)
			return ((char *)s1 + (i - j));
		i = i - j;
		i++;
	}
	return (NULL);
}
