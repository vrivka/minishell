#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
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
