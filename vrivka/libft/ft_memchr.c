/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:59:26 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/20 12:40:53 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned const char	*cs;
	unsigned char		cc;

	cc = c;
	cs = s;
	i = 0;
	while (i < n)
	{
		if (cs[i] == cc)
			return ((void *)&cs[i]);
		i++;
	}
	return (NULL);
}
