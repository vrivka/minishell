/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:33:31 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/24 13:48:30 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*cs1;
	unsigned const char	*cs2;
	size_t				r;

	i = 0;
	r = 0;
	cs1 = s1;
	cs2 = s2;
	while (i < n)
	{
		r = cs1[i] - cs2[i];
		if (r != 0)
			return (r);
		i++;
	}
	return (r);
}
