#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*dst;

	dst = (unsigned char *)str;
	while (n--)
		*dst++ = (unsigned char)c;
	return (str);
}
