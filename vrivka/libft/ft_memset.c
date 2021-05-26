/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:13:40 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/20 12:36:48 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cb;
	unsigned char	cc;
	size_t			i;

	i = 0;
	cb = b;
	cc = c;
	while (i < len)
	{
		cb[i] = cc;
		i++;
	}
	return (cb);
}
