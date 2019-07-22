#include "cw.h"

void			op_aff(t_cw *cw, size_t i_car)
{
	uint8_t		letter;

	cw->step = OP_SIZE + REGN_SIZE;
	cw->pos = PCV(cw->car[i_car]->pc + cw->step);
	cw->arg[0] = cw->map[IN(cw->pos)].v.code;
	if (cw->f.lg.dbg || cw->f.lg.vs)
		(cw->f.lg.dbg) ? dbg_log(cw, i_car) : vs_backlight_car(cw, i_car, cw->step);
	cw->car[i_car]->pc = cw->pos;
	if (!cw->f.lg.af || !(1 <= cw->arg[0] && cw->arg[0] <= REG_NUMBER))
		return ;
	letter = cw->car[i_car]->reg[IN(cw->arg[0])] % 0xFF;
	write(1, &letter, 1);
}
