#include "test.h"

t_elist *new_elem_env_list(char *env)
{
	t_elist *new;

	new = (t_elist *)malloc(sizeof(t_elist));
	if (!new)
		return (0);
	new->env = strdup(env);
	new->next = 0;
	return (new);
}

t_elist *new_env_list(char **env)
{
	t_elist *begin;
	t_elist *elst;
	int i;

	i = 0;
	elst = new_elem_env_list(env[i]);
	begin = elst;
	i++;
	while (env[i])
	{
		elst->next = new_elem_env_list(env[i]);
		elst = elst->next;
		i++;
	}
	return (begin);
}

t_elist *list_last(t_elist *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void list_add_front(t_elist **lst, t_elist *new)
{
	if (!lst)
		return ;
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

void list_add_back(t_elist *lst, t_elist *new)
{
	if (!lst)
		return ;
	lst = list_last(lst);
	lst->next = new;
}

int list_size(t_elist *lst)
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

void free_env_list(t_elist *elst)
{
	t_elist *tmp;

	tmp = elst;
	while (tmp)
	{
		tmp = elst->next;
		free(elst->env);;
		free(elst);
		elst = tmp;
	}
}

void print_env_list(t_elist *elst)
{
	int i;

	while (elst)
	{
		i = 0;
		while (elst->env[i] != '=' && elst->env[i])
			i++;
		if (elst->env[i] == '=')
			printf("%s\n", elst->env);
		elst = elst->next;
	}
}
