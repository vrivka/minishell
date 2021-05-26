#include "test.h"

void swap_string(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void sort_exp_list(char **exp)
{
	int i;
	int j;

	i = 0;
	while (exp[i])
	{
		j = i + 1;
		while (exp[j])
		{
			if (strcmp(exp[i], exp[j]) > 0)
				swap_string(&exp[i], &exp[j]);
			j++;
		}
		i++;
	}
}

void print_export(char **exp)
{
	int a;
	int i;
	int j;

	a = 0;
	while (exp[a])
	{
		i = 0;
		while (exp[a][i] != '=' && exp[a][i] != 0)
			i++;
		if (exp[a][i] == 0)
			printf("declare -x %s\n", exp[a]);
		else
		{
			j = i + 1;
			printf("declare -x %.*s=\"%s\"\n", i, exp[a], &exp[a][j]);
		}
		a++;
	}
}

char **env_to_exp(t_elist *elst)
{
	char **exp;
	int i;
	int n;

	n = list_size(elst);
	exp = (char **)malloc(sizeof(char *) * n);
	i = 0;
	while (i < n - 1)
	{
		exp[i] = strdup(elst->env);
		elst = elst->next;
		i++;
	}
	exp[i] = NULL;
	return (exp);
}

int exp_size(char **exp)
{
	int i;

	i = 0;
	while (exp[i])
		i++;
	return (i);
}

void free_exp(char **exp, int i)
{
	while (i >= 0)
	{
		free(exp[i]);
		i--;
	}
	free(exp);
}

size_t nbyte(char *env)
{
	size_t i;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	return (i - 1);
}

t_elist *have_env(char *env, t_elist *elst)
{
	t_elist *tmp;

	while (elst)
	{
		tmp = elst;
		if (strncmp(env, tmp->env, nbyte(env)) == 0)
			return (tmp);
		elst = elst->next;
	}
	return (NULL);
}

//void change_env(char *env, t_elist **elst)
//{
//
//}

void export_func(char *env, t_elist **elst)
{
	char **exp;
	t_elist *e;

	if (env == NULL)
	{
		exp = env_to_exp(*elst);
		sort_exp_list(exp);
		print_export(exp);
		free_exp(exp, exp_size(exp) - 1);
	}
	else
	{
		e = have_env(env, *elst);
		if (e != 0);
//			change_env(env, &(*elst));
		else
			list_add_front(&(*elst), new_elem_env_list(env));
	}
}
