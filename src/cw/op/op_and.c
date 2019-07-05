#include "cw.h"

void			op_and(t_cw *cw, uint8_t i_car)
{
	if (codage_validator(cw, i_car, AND))
		return ;
	if (cw->cod.arg.v1 & IND_CODE || cw->cod.arg.v1 & DIR_CODE)
		cw->car[i_car]->reg[cw->arg[2]] = code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	else
		cw->car[i_car]->reg[cw->arg[2]] = cw->car[i_car]->reg[cw->arg[0]];
	if (cw->cod.arg.v2 & IND_CODE || cw->cod.arg.v2 & DIR_CODE)
		cw->car[i_car]->reg[cw->arg[2]] &= code_to_byte(cw->map, cw->arg[1], REG_SIZE);
	else
		cw->car[i_car]->reg[cw->arg[2]] &= cw->car[i_car]->reg[cw->arg[1]];
	cw->car[i_car]->carry = (cw->car[i_car]->reg[cw->arg[2]]) ? 0 : 1;
	cw->car[i_car]->pc = PC_INC(cw->car[i_car]->pc, cw->step);
	vs_log(cw, AND);
}
