#include "cw.h"

void			op_aff(t_cw *cw, uint8_t i_car)
{
	cw->pos = cw->car[i_car]->pc + OP_SIZE + REG_SIZE;
	cw->car[i_car]->pc = PC_INC(cw->pos, 0);
	if (!(1 <= cw->map[PC(cw->pos)] && cw->map[IN(cw->pos)] <= REG_NUMBER))
		return ;
	cw->arg[0] = cw->car[i_car]->reg[IN(cw->map[IN(cw->pos)])] % 0xFF;
	write(1, &cw->arg[0], 1);
	vs_log(cw, AFF);
}
