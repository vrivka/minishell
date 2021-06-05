#include "libft.h"

static unsigned int	in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	size_decision(char *s1, char *start, char *end)
{
	if (!*s1 || end == start)
		return (2);
	else
		return (end - start + 2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	unsigned int	size;
	char			*start;
	char			*end;
	char			*trim;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && in_set(s1[i], set))
		i++;
	start = (char *)&s1[i];
	i = ft_strlen((char *)s1) - 1;
	if (i != -1)
		while (i >= 0 && in_set(s1[i], set))
			i--;
	end = (char *)&s1[i];
	size = size_decision((char *)s1, start, end);
	trim = malloc(sizeof(char) * size);
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, start, size);
	return (trim);
}
