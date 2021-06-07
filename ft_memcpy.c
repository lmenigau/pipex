#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptr;

	ptr = dst;
	while (n--)
		*ptr++ = *(char *)src++;
	return (dst);
}
