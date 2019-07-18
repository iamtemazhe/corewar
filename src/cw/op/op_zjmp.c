#include "cw.h"

void			op_zjmp(t_cw *cw, uint8_t i_car)
{
	cw->step = OP_SIZE + cw->op[ZJMP].label_size;
	cw->arg[0] = code_to_byte(cw->map, cw->car[i_car]->pc + cw->step, cw->op[ZJMP].label_size);
	cw->err = (cw->car[i_car]->carry) ? 0 : -1;
	if (cw->flg & DEBUG)
		dbg_log(cw, i_car);
	cw->car[i_car]->pc = (cw->car[i_car]->carry) ? PCV(cw->car[i_car]->pc + (int16_t)cw->arg[0] % IDX_MOD) :
													PCV(cw->car[i_car]->pc + cw->step);
	if (cw->flg & VISU)
		vs_log(cw, i_car, 0);
}
