#include "minishell.h"

void echo_func(char **av)
{
	int i;
	int c;

	i = 1;
	c = 0;
	if (!av[i])
	{
		printf("\n");
		return ;
	}
	if (!ft_strncmp(av[i], "-n\0", 3))
	{
		c = 1;
		i++;
	}
	while (av[i + 1])
	{
		printf("%s ", av[i]);
		i++;
	}
	printf("%s", av[i]);
	if (c != 1)
		printf("\n");
}
