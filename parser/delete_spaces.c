#include "minishell.h"

char	*del_start_sp(char *s1)
{
	char	*s2;
	int		i;

	s2 = NULL;
	i = 0;
	if (s1[i] == ' ')
	{
		while (s1[i] == ' ')
			i++;
		s2 = ft_cutstr_begin(s1, i);
		return (s2);
	}
	return (s1);
}

char	*del_end_sp(char *s1)
{
	char	*s2;
	int		i;
	int		len;

	s2 = NULL;
	len = ft_strlen(s1);
	i = len - 1;
	if (s1[i] == ' ')
	{
		while (s1[i] == ' ')
		{
			if (s1[i - 1] == '\\')
				break ;
			i--;
		}
		s2 = ft_cutstr_end(s1, (i + 1));
		return (s2);
	}
	return (s1);
}
