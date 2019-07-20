#include "cw.h"

void			op_fork(t_cw *cw, size_t i_car)
{
	uint8_t		id_car;

	cw->step = OP_SIZE + cw->op[FORK].label_size;
	cw->arg[0] = code_to_byte(cw->map, cw->car[i_car]->pc + cw->step, cw->op[FORK].label_size);
	cw->pos = (int16_t)cw->arg[0] % IDX_MOD;
	id_car = add_car(cw, i_car);
	if (cw->f.lg.dbg || cw->f.lg.vs)
		(cw->f.lg.dbg) ? dbg_log_cod(cw, i_car) : vs_backlight_car(cw, i_car, cw->step);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
