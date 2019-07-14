#include "cw.h"

void			op_aff(t_cw *cw, uint8_t i_car)
{
	if (cw->flg & DEBUG)
		debug_log(cw, i_car);
	cw->pos = cw->car[i_car]->pc + OP_SIZE + REGN_SIZE;
	cw->car[i_car]->pc = PCV(cw->pos);
	if (!(1 <= cw->map[PC(cw->pos)] && cw->map[PC(cw->pos)] <= REG_NUMBER))
		return ;
	cw->arg[0] = cw->car[i_car]->reg[IN(cw->map[PC(cw->pos)])] % 0xFF;
	write(1, &cw->arg[0], 1);
	if (cw->flg & VISU)
		vs_log(cw, i_car);
}
