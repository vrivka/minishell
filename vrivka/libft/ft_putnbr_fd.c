/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:41:57 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/17 13:46:05 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		size;

	size = 1000000000;
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n == 0)
		ft_putchar_fd('0', fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = n * -1;
		}
		while (n / size == 0)
			size = size / 10;
		while (size >= 1)
		{
			c = n / size + 48;
			n = n % size;
			size = size / 10;
			ft_putchar_fd(c, fd);
		}
	}
}
