#include "test.h"
#include <stdio.h>
#include <string.h>

size_t		code_to_byte(const void *src, uint32_t pos, size_t n);
void		byte_to_code(void *dst, uint32_t pos, const void *src, size_t n);

int			main()
{
	t_cws	cw;

	cw.flg.b = 0xab;
	printf("FLG = %#x\n", cw.flg.b);
	printf("VIS = %#x, DEB = %#x, N = %#x, DUMP = %#x\n", cw.flg.f.v1, cw.flg.f.v2, cw.flg.f.v3, cw.flg.f.v4);


	/*uint8_t	b[4] = {0xAA, 0xBB, 0xCC, 0xEE};

	uint32_t i;
	memcpy(&i, &b[0], 4);
	printf("b = %#x\n", i);
	unsigned char	a[4] = {0xFF, 0xAA, 0xDD, 0xCC};
	uint32_t		j;
	j = (uint32_t)code_to_byte(a, 0, 4);
	printf("a = %#x\n", j);
	unsigned char	c[4];
	byte_to_code(c, 0,  &j, 4);
	printf("c = %#x, %#x, %#x, %#x\n", c[0], c[1], c[2], c[3]);

	cw.cod.age = 0x37;
	printf("codage = %#x, arg1 = %#x, arg2 = %#x, arg3 = %#x, arg4 = %#x\n", cw.cod.age, cw.cod.arg.v1, cw.cod.arg.v2, cw.cod.arg.v3, cw.cod.arg.v4);
	printf("pos_45 = %d, pos_4097 = %d, pos_4100 = %d\n", PC(45), PC(4097), PC(4100));*/
	return (0);
}
