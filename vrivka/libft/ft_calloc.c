/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:11:48 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/20 13:23:59 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*i;
	size_t	s;

	s = count * size;
	i = (char *)malloc(s);
	if (i == NULL)
		return (NULL);
	ft_bzero(i, s);
	return ((void *)i);
}
