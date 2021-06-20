#include "minishell.h"

void	open_dup_pipes(int i)
{
	if (i)
	{
		dup2(g_msh.pipe_fd[i - 1][0], 0);
		close(g_msh.pipe_fd[i - 1][0]);
		close(g_msh.pipe_fd[i - 1][1]);
	}
	if (i + 1 < g_msh.pipe_count)
	{
		dup2(g_msh.pipe_fd[i][1], 1);
		close(g_msh.pipe_fd[i][1]);
		close(g_msh.pipe_fd[i][0]);
	}
}

void	close_if(int fd1, int fd2)
{
	if (fd1 < 0 || fd2 < 0)
		exit (1);
	dup2(fd1, 0);
	dup2(fd2, 1);
}

int	it_builtin(int i)
{
	if (!ft_strncmp(g_msh.pipe[i].args[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "cd", 3))
		return (2);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "pwd", 4))
		return (3);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "export", 7))
		return (4);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "unset", 6))
		return (5);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "env", 4))
		return (6);
	else if (!ft_strncmp(g_msh.pipe[i].args[0], "exit", 5))
		return (7);
	else
		return (0);
}

int	exec_builtin(int i, int n)
{
	int	r;

	r = 0;
	if (n == 1)
		r = echo_func(g_msh.pipe[i].args);
	else if (n == 2)
		r = cd_func(g_msh.pipe[i].args);
	else if (n == 3)
		r = pwd_func();
	else if (n == 4)
		r = export_func(g_msh.pipe[i].args);
	else if (n == 5)
		r = unset_func(g_msh.pipe[i].args);
	else if (n == 6)
		r = env_func();
	else if (n == 7)
		r = exit_func(g_msh.pipe[i].args);
	return (r);
}

int	check_exec_name(char *bin, char *name)
{
	char	*p;
	int		len;

	len = ft_strlen(bin);
	p = ft_strnstr(bin, name, len);
	if (p == NULL)
		return (0);
	else
	{
		if (p[ft_strlen(name)] == '\0')
			return (1);
		else
			check_exec_name(p, name);
	}
	return (0);
}
