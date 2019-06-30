#include "cw.h"

void			op_aff(t_cw *cw, uint8_t i_car)
{
	cw->pos = cw->car[i_car].pc + OP_SIZE + REG_SIZE;
	cw->car[i_car].pc = cw->pos;
	if (!(1 <= cw->map[PC(cw->pos)] && cw->map[PC(cw->pos)] <= REG_NUMBER))
	{
		cw->err = -1;
		return ;
	}
	cw->arg[0] = cw->car[i_car].reg[cw->map[PC(cw->pos)] - 1] % 0xFF;
	write(1, &cw->arg[0], 1);
}