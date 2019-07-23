#include "cw.h"

void			op_and(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, AND))
		return ;
	cw->car[i_car]->reg[IN(cw->arg[2])] = (cw->cod.arg.v1 == REG_CODE) ?\
										cw->car[i_car]->reg[IN(cw->arg[0])] :\
										code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	cw->car[i_car]->reg[IN(cw->arg[2])] &= (cw->cod.arg.v2 == REG_CODE) ?\
										cw->car[i_car]->reg[IN(cw->arg[1])] :\
										code_to_byte(cw->map, cw->arg[1], REG_SIZE);
	cw->car[i_car]->carry = (cw->car[i_car]->reg[IN(cw->arg[2])]) ? 0 : 1;
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}