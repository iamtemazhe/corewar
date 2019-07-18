#include "cw.h"

void			op_st(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, ST))
		return ;
	if (cw->cod.arg.v2 == IND_CODE)
		byte_to_code(cw->map, cw->arg[1], &cw->car[i_car]->reg[IN(cw->arg[0])], REG_SIZE);
	else
		cw->car[i_car]->reg[IN(cw->arg[1])] = cw->car[i_car]->reg[IN(cw->arg[0])];
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	cw->pos = cw->arg[1];
	if (cw->flg & VISU)
		vs_log(cw, i_car, (cw->cod.arg.v2 == IND_CODE) ? ST + 1 : 0);
}