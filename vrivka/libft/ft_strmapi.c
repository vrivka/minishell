/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:37:48 by vrivka            #+#    #+#             */
/*   Updated: 2020/11/24 11:57:32 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*d;
	int		i;
	int		sl;

	i = 0;
	if (s == NULL)
		return (NULL);
	sl = ft_strlen(s);
	if (!(d = (char *)malloc(sizeof(char) * (sl + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		d[i] = f(i, s[i]);
		i++;
	}
	d[i] = '\0';
	return (d);
}
