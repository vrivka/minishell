/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:03:45 by epilar            #+#    #+#             */
/*   Updated: 2020/11/01 15:49:29 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	n;

	d = 0;
	n = 0;
	s = 0;
	while (dst[d] && d < size)
		d++;
	while (src[n] && d + n + 1 < size)
	{
		dst[d + n] = src[n];
		n++;
	}
	while (src[s] != '\0')
		s++;
	if (d != size)
		dst[d + n] = '\0';
	return (d + s);
}
