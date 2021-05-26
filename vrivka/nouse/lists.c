t_list *listnew(void *data)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}

void list_add_front(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (!(*lst))
		return ;
	if (!new)
		return ;
	new->next = *lst;
	new = *lst;
}

int list_size2(t_list *lst)
{
	int i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != 0)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_list *list_last(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void list_add_back(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (!(*lst))
		return ;
	*lst = list_last(*lst);
	(*lst)->next = new;
}

