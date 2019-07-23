#include "cw.h"

void			op_add(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, ADD))
		return ;
	cw->car[i_car]->reg[IN(cw->arg[2])] = cw->car[i_car]->reg[IN(cw->arg[0])] +\
											cw->car[i_car]->reg[IN(cw->arg[1])];
	cw->car[i_car]->carry = (cw->car[i_car]->reg[IN(cw->arg[2])]) ? 0 : 1;
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
