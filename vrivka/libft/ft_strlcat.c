/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:17:44 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/24 15:45:15 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t d;
	size_t i;
	size_t s;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	i = 0;
	if (dst[0] == '\0')
	{
		return (ft_strlcpy(dst, src, dstsize));
	}
	else if (d > dstsize)
	{
		d++;
		i = ft_strlcpy(&dst[d], src, dstsize);
		return (dstsize + i);
	}
	else if (d <= dstsize)
	{
		ft_strlcpy(&dst[d], src, dstsize - d);
		return (d + s);
	}
	return (d);
}
