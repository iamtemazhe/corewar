#include "cw.h"

void			op_aff(t_cw *cw, size_t i_car)
{
	uint8_t		letter;

	cw->pos = cw->car[i_car]->pc + OP_SIZE + REGN_SIZE;
	cw->arg[0] = cw->map[PC(cw->pos)];
	if (cw->f.lg.dbg)
		dbg_log(cw, i_car);
	cw->car[i_car]->pc = PCV(cw->pos);
	if (!cw->f.lg.af || !(1 <= cw->arg[0] && cw->arg[0] <= REG_NUMBER))
		return ;
	letter = cw->car[i_car]->reg[IN(cw->arg[0])] % 0xFF;
	write(1, &letter, 1);
	if (cw->f.lg.vs)
		vs_log(cw, i_car, 0);
}
