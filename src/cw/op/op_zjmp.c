#include "cw.h"

void			op_zjmp(t_cw *cw, uint8_t i_car)
{
	cw->step = OP_SIZE + cw->op[ZJMP].label_size;

	cw->arg[0] = code_to_byte(cw->map, cw->car[i_car]->pc + cw->step, cw->op[ZJMP].label_size);
	if (!cw->car[i_car]->carry)
		cw->err = -1;
	if (cw->flg & DEBUG)
		dbg_log(cw, i_car);
	if (!cw->car[i_car]->carry)
		cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	else
		cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + (int16_t)cw->arg[0] % IDX_MOD);
	if (cw->flg & VISU)
		vs_log(cw, i_car);
}
