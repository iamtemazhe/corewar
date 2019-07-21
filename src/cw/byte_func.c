#include "cw.h"

size_t		code_to_byte(const void *src, int32_t pos, size_t n)
{
	size_t	dst;

	dst = 0;
	while (n-- > 0)
		dst += ((uint8_t *)src)[PC(pos - n)] << (n * 8);
	return (dst);
}

void		byte_to_code(void *dst, int32_t pos, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (n-- > 0)
	{
		((uint8_t *)dst)[PCV(pos + i)] = ((uint8_t *)src)[n];
		i++;
	}
}