/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:51:04 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/20 12:51:11 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*cdst;
	unsigned const char	*csrc;
	unsigned char		cc;
	size_t				i;

	cdst = dst;
	csrc = src;
	cc = c;
	i = 0;
	while (i < n)
	{
		cdst[i] = csrc[i];
		if (csrc[i] == cc)
		{
			i++;
			return (&cdst[i]);
		}
		i++;
	}
	return (NULL);
}
