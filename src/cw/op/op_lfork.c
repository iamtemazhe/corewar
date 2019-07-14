#include "cw.h"

void			op_lfork(t_cw *cw, uint8_t i_car)
{
	uint8_t		id_car;

	id_car = add_car(cw, i_car);
	cw->step = OP_SIZE + cw->op[LFORK].label_size;
	cw->arg[0] = code_to_byte(cw->map, cw->car[i_car]->pc + cw->step, cw->op[LFORK].label_size);
	if (cw->flg & DEBUG)
		dbg_log(cw, i_car);
	cw->car[id_car]->pc = PCV(cw->car[i_car]->pc + (int16_t)cw->arg[0]);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	if (cw->flg & VISU)
		vs_log(cw, i_car);
}
