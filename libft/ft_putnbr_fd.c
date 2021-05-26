/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:32:51 by epilar            #+#    #+#             */
/*   Updated: 2020/11/08 10:13:53 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnbr_fd(int n, int fd)
{
	int				i;
	char			s[12];
	long long int	nl;

	nl = (long long int)n;
	if (nl == 0)
		ft_putchar_fd('0', fd);
	if (nl < 0)
	{
		ft_putchar_fd('-', fd);
		nl = -nl;
	}
	i = 0;
	while (nl > 0)
	{
		s[i] = nl % 10 + '0';
		i++;
		nl /= 10;
	}
	i--;
	while (i >= 0)
	{
		ft_putchar_fd(s[i], fd);
		i--;
	}
}
