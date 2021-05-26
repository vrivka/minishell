/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:57:53 by epilar            #+#    #+#             */
/*   Updated: 2020/11/11 12:17:11 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*old;

	if (!lst)
		return ;
	while (*lst)
	{
		old = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = old;
	}
	*lst = NULL;
}
