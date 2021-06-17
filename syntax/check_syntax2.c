#include "minishell.h"

int	check_mid_pipe(char *tmp)
{
	int	i;

	g_msh.flags = NOFLG;
	i = 0;
	while (tmp[i])
	{
		set_flags(tmp[i]);
		if (tmp[i] == '|' && !check_flags())
		{
			i++;
			while (tmp[i] == ' ')
				i++;
			if (ft_strchr("<>;|", tmp[i]))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	check_pipe(char *s)
{
	char	*tmp;

	tmp = ft_strdup(s);
	if (tmp == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	tmp = del_start_sp(tmp);
	tmp = del_end_sp(tmp);
	if (tmp[0] == '|' || tmp[ft_strlen(tmp) - 1] == '|' || check_mid_pipe(tmp))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

int	check_semi(void)
{
	int	i;

	i = 0;
	while (i < g_msh.semi_count)
	{
		if (!ft_strlen(g_msh.semi[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_alone_rd(int i, int n)
{
	if (((!ft_strcmp("<", g_msh.pipe[i].rd[n]) || \
		!ft_strcmp(">", g_msh.pipe[i].rd[n]) || \
		!ft_strcmp("<<", g_msh.pipe[i].rd[n]) || \
		!ft_strcmp(">>", g_msh.pipe[i].rd[n])) && \
		g_msh.pipe[i].rd[n + 1] == NULL) || \
		((!ft_strcmp("<", g_msh.pipe[i].rd[n]) || \
		!ft_strcmp(">", g_msh.pipe[i].rd[n]) || \
		!ft_strcmp("<<", g_msh.pipe[i].rd[n]) || \
		!ft_strcmp(">>", g_msh.pipe[i].rd[n])) && \
		(!ft_strcmp("<", g_msh.pipe[i].rd[n + 1]) || \
		!ft_strcmp(">", g_msh.pipe[i].rd[n + 1]) || \
		!ft_strcmp("<<", g_msh.pipe[i].rd[n + 1]) || \
		!ft_strcmp(">>", g_msh.pipe[i].rd[n + 1]))))
		return (1);
	else
		return (0);
}
