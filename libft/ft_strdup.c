/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 09:58:08 by epilar            #+#    #+#             */
/*   Updated: 2020/11/08 12:27:10 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dst;
	int		s;
	int		i;

	s = 0;
	i = 0;
	while (str[s])
		s++;
	if (!(dst = (char *)malloc((s + 1) * sizeof(char))))
		return (NULL);
	while (i < s)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
