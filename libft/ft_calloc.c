/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:48:59 by epilar            #+#    #+#             */
/*   Updated: 2020/11/08 12:26:00 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t s)
{
	char	*p;
	size_t	sum;
	int		i;

	i = 0;
	sum = n * s;
	if (!(p = (char *)malloc(sum)))
		return (NULL);
	while (sum--)
		p[i++] = 0;
	return ((void *)p);
}
