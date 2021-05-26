/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:34:28 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/24 20:12:25 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		charcount(int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int		whatsign(int n)
{
	if (n < 0)
		return (-1);
	else
		return (1);
}

static char		*itoamain(int n, int i, int sign)
{
	char *s;

	if (!(s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (sign == -1)
		n = n * -1;
	s[i] = '\0';
	i--;
	while (i >= 0)
	{
		s[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	if (sign == -1)
		s[0] = '-';
	return (s);
}

char			*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		sign;

	i = charcount(n);
	sign = whatsign(n);
	if (n == -2147483648)
		s = ft_strdup("-2147483648");
	else if (n == -0)
		s = ft_strdup("0");
	else
		s = itoamain(n, i, sign);
	return (s);
}
