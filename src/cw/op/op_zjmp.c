#include "cw.h"

void			op_zjmp(t_cw *cw, uint8_t i_car)
{
	if (cw->car[i_car]->carry)
		cw->car[i_car]->pc = PC_INC(cw->car[i_car]->pc, cw->map[PC(cw->arg[0])] % IDX_MOD);
	vs_log(cw, ZJMP);
}
