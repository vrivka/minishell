#include "minishell.h"

int error_func(char *error_str, int exit_code, int ex_ret, char *arg)
{
	if (error_str)
	{
		printf("%s\n", error_str);
		if (ex_ret)
			return (exit_code);
		else
			exit(exit_code);
	}
	else
	{
		printf("minishell: %s: %s: %s\n", "cd", arg, strerror(errno));
		if (ex_ret)
			return (exit_code);
		else
			exit(exit_code);
	}
}