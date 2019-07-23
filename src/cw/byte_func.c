#include "cw.h"

size_t		code_to_byte(const union u_map *src, int32_t pos, size_t n)
{
	size_t	dst;

	dst = 0;
	while (n-- > 0)
		dst += src[PC(pos - n)].v.code << (n * 8);
	return (dst);
}

void		byte_to_code(union u_map *dst, int32_t pos, const void *src,\
														size_t n)
{
	size_t	i;

	i = 0;
	while (n-- > 0)
	{
		dst[PCV(pos + i)].v.code = ((uint8_t *)src)[n];
		i++;
	}
}
