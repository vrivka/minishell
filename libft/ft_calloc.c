#include "libft.h"

void	*ft_calloc(size_t n, size_t s)
{
	char	*p;
	size_t	sum;
	int		i;

	i = 0;
	sum = n * s;
	p = (char *)malloc(sum);
	if (p == NULL)
		return (NULL);
	while (sum--)
		p[i++] = 0;
	return ((void *)p);
}
