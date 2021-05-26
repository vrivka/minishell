/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:23:35 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/25 19:50:42 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	r;

	i = 0;
	r = 0;
	while (i < n)
	{
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (r != 0 || s1[i] == '\0')
			return (r);
		i++;
	}
	return (r);
}
