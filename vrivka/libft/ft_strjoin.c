/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:33:31 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/24 11:59:04 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		i;
	int		slen[2];

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	slen[0] = ft_strlen(s1);
	slen[1] = ft_strlen(s2);
	if (!(dst = (char *)malloc(sizeof(char) * ((slen[0] + slen[1]) + 1))))
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		dst[i] = *s2;
		s2++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
