#include "minishell.h"

int	error_func(char *error_str, int exit_code, int ex_ret, char *arg)
{
	int	fd;

	fd = dup(1);
	dup2(2, 1);
	if (error_str)
	{
		if (arg)
			printf(error_str, arg);
		else
			printf("%s\n", error_str);
	}
	else
		printf("minishell: %s: %s\n", arg, strerror(errno));
	dup2(fd, 1);
	close(fd);
	if (ex_ret)
		return (exit_code);
	else
		exit(exit_code);
}
