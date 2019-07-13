#include "cw.h"

void			op_add(t_cw *cw, uint8_t i_car)
{
	if (codage_validator(cw, i_car, ADD))
		return ;
	cw->car[i_car]->reg[cw->arg[2]] = cw->car[i_car]->reg[cw->arg[0]] +\
										cw->car[i_car]->reg[cw->arg[1]];
	cw->car[i_car]->carry = (cw->car[i_car]->reg[cw->arg[2]]) ? 0 : 1;
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	vs_log(cw, ADD, i_car);
}
