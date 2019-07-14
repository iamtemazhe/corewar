#include "cw.h"

void			op_sub(t_cw *cw, uint8_t i_car)
{
	if (codage_validator(cw, i_car, SUB))
		return ;
	cw->car[i_car]->reg[cw->arg[2]] = cw->car[i_car]->reg[cw->arg[0]] -\
										cw->car[i_car]->reg[cw->arg[1]];
	cw->car[i_car]->carry = (cw->car[i_car]->reg[cw->arg[2]]) ? 0 : 1;
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	if (cw->flg & VISU)
		vs_log(cw, i_car);
}
