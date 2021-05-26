/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:43:39 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/25 20:45:25 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strnstrmain(const char *h, const char *n, size_t len, size_t nl)
{
	size_t i1;
	size_t i2;
	size_t f;

	i1 = 0;
	i2 = 0;
	while (i1 < len)
	{
		f = i1;
		while (h[f] == n[i2] && h[f] != '\0' && f < len)
		{
			f++;
			i2++;
		}
		if (i2 == nl)
			return ((char *)&h[i1]);
		if (h[f] == '\0')
			break ;
		i2 = 0;
		i1++;
	}
	return (NULL);
}

char		*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t nl;

	nl = ft_strlen(n);
	if (h == NULL && len == 0)
		return (NULL);
	if (nl == 0)
		return ((char *)h);
	return (strnstrmain(h, n, len, nl));
}
