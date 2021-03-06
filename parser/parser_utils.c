#include "minishell.h"

int	get_sqstr_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\'')
		i++;
	return (i);
}

char	*get_sq_str(t_pars *pars)
{
	char	*str;
	int		len;
	int		i;

	len = get_sqstr_len(pars->s);
	str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (str == NULL)
		error_func(ERROR_MEM, 1, 0, NULL);
	i = 0;
	while (pars->s[i] != '\'')
	{
		str[i] = pars->s[i];
		i++;
	}
	pars->s = ft_cutstr_begin(pars->s, (i + 1));
	return (str);
}

void	args2lower(void)
{
	int		i;
	int		n;

	i = 0;
	while (i < g_msh.pipe_count)
	{
		n = 0;
		if (g_msh.pipe[i].args != NULL)
		{
			if (g_msh.pipe[i].args[0] != NULL)
			{
				while (g_msh.pipe[i].args[0][n] != '\0')
				{
					g_msh.pipe[i].args[0][n] = \
					ft_tolower(g_msh.pipe[i].args[0][n]);
					n++;
				}
			}
		}
		i++;
	}
}

void	change_sp2us(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while ((*s)[i] != '\0')
		{
			if ((*s)[i] == ' ')
				(*s)[i] = '_';
			i++;
		}
	}
	else
		return ;
}
