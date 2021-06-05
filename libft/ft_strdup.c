#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dst;
	int		s;
	int		i;

	s = 0;
	i = 0;
	while (str[s])
		s++;
	dst = (char *)malloc((s + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (i < s)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
