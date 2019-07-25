#include "cw.h"

void			op_sub(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, SUB))
		return ;
	cw->pos = cw->car[i_car]->reg[IN(cw->arg[0])] -\
									cw->car[i_car]->reg[IN(cw->arg[1])];
	if (cw->arg[2] > 0x1 || (cw->arg[2] == 0x1 && 1 <= -cw->pos && -cw->pos <= cw->num_of_champs))
	{
		cw->car[i_car]->reg[IN(cw->arg[2])] = cw->pos;
		cw->car[i_car]->carry = (cw->car[i_car]->reg[IN(cw->arg[2])]) ? 0 : 1;
	}
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
