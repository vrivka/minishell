#include "minishell.h"

int	exec_without_pipes(void)
{
	int	r;
	int	fd_1;
	int	fd_0;

	r = it_builtin(0);
	if (r)
	{
		fd_0 = dup(0);
		fd_1 = dup(1);
		if (g_msh.pipe[0].rd)
		{
			if (g_msh.pipe[0].l_fd < 0 || g_msh.pipe[0].r_fd < 0)
				return (1);
			dup2(g_msh.pipe[0].l_fd, 0);
			dup2(g_msh.pipe[0].r_fd, 1);
		}
		r = exec_builtin(0, r);
		dup2(fd_0, 0);
		dup2(fd_1, 1);
		close(fd_0);
		close(fd_1);
	}
	else
		r = exec_func(g_msh.pipe[0].args);
	return (r);
}

void	check_dir(char *arg, int st)
{
	struct stat		buf;
	DIR				*fd;

	if (!ft_strncmp(arg, "/", 1) || !ft_strncmp(arg, "./", 2)
		|| !ft_strncmp(arg, "../", 3))
	{
		st = stat(arg, &buf);
		if (st < 0)
			error_func(NULL, 127, 0, arg);
		else
		{
			fd = opendir(arg);
			if (!fd)
				error_func("minishell: %s: Permission denied\n", 126, 0, arg);
			else
				error_func("minishell: %s: is a directory\n", 126, 0, arg);
		}
	}
	else if (!ft_strcmp(arg, "."))
	{
		error_func("minishell: .: filename argument required", 1, 1, NULL);
		error_func(".: usage: . filename [arguments]", 2, 0, NULL);
	}
	else
		error_func("minishell: %s: command not found\n", 127, 0, arg);
}

void	signals_check(char **av)
{
	if (check_exec_name(av[0], EXEC_F_NAME))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, sig_handler_exec);
		signal(SIGQUIT, sig_handler_exec);
	}
}

int	exec_func(char **av)
{
	int	r;

	signals_check(av);
	g_msh.pid = fork();
	if (g_msh.pid < 0)
		error_func(NULL, 1, 0, NULL);
	else if (g_msh.pid == 0)
	{
		if (g_msh.pipe[0].rd)
			close_if(g_msh.pipe[0].l_fd, g_msh.pipe[0].r_fd);
		r = execve(g_msh.pipe[0].bin_path, av, g_msh.envp);
		if (r < 0)
			check_dir(g_msh.pipe[0].bin_path, 0);
		exit(r);
	}
	waitpid(0, &r, 0);
	g_msh.pid = 0;
	return (WEXITSTATUS(r));
}
