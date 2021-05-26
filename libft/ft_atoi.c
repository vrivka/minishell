/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:13:09 by epilar            #+#    #+#             */
/*   Updated: 2020/11/02 16:16:09 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		res;
	int		sign;
	int		k;

	i = 0;
	res = 0;
	k = 0;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
				str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	sign = ((str[i] == '-') ? -1 : 1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		k++;
		if (k >= 19 && sign == 1)
			return (-1);
		if (k >= 19 && sign == -1)
			return (0);
	}
	return (res * sign);
}
