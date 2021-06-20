#include "minishell.h"

int	get_pipe_num(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	g_msh.flags = NOFLG;
	while (s[i])
	{
		set_flags(s[i]);
		if (s[i] == '|' && !check_flags())
			n++;
		i++;
	}
	return (n);
}

int	get_pipestr_len(char *s)
{
	int	i;

	i = 0;
	g_msh.flags = NOFLG;
	while (s[i])
	{
		set_flags(s[i]);
		if (s[i] == '|' && !check_flags())
			break ;
		i++;
	}
	return (i);
}

char	*get_pipe_str(char **s)
{
	char	*tmp;
	int		len;

	len = get_pipestr_len(*s);
	tmp = ft_substr(*s, 0, len);
	if (tmp == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	if ((*s)[len] == '|')
		*s = ft_cutstr_begin(*s, (len + 1));
	return (tmp);
}
