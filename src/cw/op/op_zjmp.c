#include "cw.h"

void			op_zjmp(t_cw *cw, size_t i_car)
{
	cw->step = OP_SIZE + cw->op[ZJMP].label_size;
	cw->arg[0] = (int16_t)code_to_byte(cw->map, cw->car[i_car]->pc + cw->step,\
														cw->op[ZJMP].label_size);
	cw->err = (cw->car[i_car]->carry) ? 0 : -1;
	cw->step = (cw->car[i_car]->carry) ? cw->arg[0] % IDX_MOD : cw->step;
	if (cw->f.lg.dbg || cw->f.lg.vs)
		(cw->f.lg.dbg) ? dbg_log(cw, i_car) : vs_backlight_car(cw, i_car, cw->step);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
