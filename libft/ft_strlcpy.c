#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	if (src == NULL)
		return (0);
	while (src[count] != '\0')
		count++;
	i = 0;
	if (size)
	{
		while (i < size - 1)
		{
			if (src[i] == '\0')
				break ;
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	return (count);
}
