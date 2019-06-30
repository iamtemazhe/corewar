#include "cw.h"

size_t		code_to_byte(const void *src, uint32_t pos, size_t n)
{
	size_t	i;
	size_t	dst;

	i = 0;
	dst = 0;
	while (i < n)
	{
		dst += ((uint8_t *)src)[PC(pos + n - i)] << (i * 8);
		i++;
	}
	return (dst);
}

void		byte_to_code(void *dst, uint32_t pos, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((uint8_t *)dst)[PC(pos + n - i)] = ((uint8_t *)src)[i];
		i++;
	}
}