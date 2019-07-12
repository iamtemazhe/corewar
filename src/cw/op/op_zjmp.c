#include "cw.h"

void			op_zjmp(t_cw *cw, uint8_t i_car)
{
	if (cw->car[i_car]->carry)
	{
		cw->pos = cw->car[i_car]->pc + cw->op[ZJMP].label_size;
		cw->pos = code_to_byte(cw->map, cw->pos, cw->op[ZJMP].label_size) % IDX_MOD;
		cw->car[i_car]->pc = PC_INC(cw->car[i_car]->pc, cw->pos);
	}
	vs_log(cw, ZJMP);
}
