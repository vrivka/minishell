/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:34:39 by epilar            #+#    #+#             */
/*   Updated: 2020/11/08 12:33:10 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int		get_sym_num(long nl, int sign)
{
	unsigned int		i;

	i = 0;
	if (nl == 0)
		return (1);
	while (nl > 0)
	{
		nl /= 10;
		i++;
	}
	if (sign == -1)
		i++;
	return (i);
}

static void				converter(char *s, long nl, unsigned int sym_num,
						int sign)
{
	s[sym_num] = '\0';
	sym_num--;
	if (nl == 0)
		s[0] = '0';
	while (nl > 0)
	{
		s[sym_num] = nl % 10 + '0';
		sym_num--;
		nl /= 10;
	}
	if (sign == -1)
		s[0] = '-';
}

char					*ft_itoa(int n)
{
	char				*s;
	long				nl;
	unsigned int		sym_num;
	int					sign;

	sign = 1;
	if (n < 0)
	{
		nl = (long)n * -1;
		sign = -1;
	}
	else
		nl = (long)n;
	sym_num = get_sym_num(nl, sign);
	if (!(s = (char *)malloc(sizeof(char) * (sym_num + 1))))
		return (NULL);
	converter(s, nl, sym_num, sign);
	return (s);
}
