#include "cw.h"

void			op_or(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, OR))
		return ;
	if (cw->cod.arg.v1 == IND_CODE || cw->cod.arg.v1 == DIR_CODE)
		cw->car[i_car]->reg[IN(cw->arg[2])] = code_to_byte(cw->map, cw->arg[0],\
			(cw->cod.arg.v1 == IND_CODE) ? IND_SIZE : cw->op[OR].label_size);
	else
		cw->car[i_car]->reg[IN(cw->arg[2])] = cw->car[i_car]->reg[IN(cw->arg[0])];
	if (cw->cod.arg.v2 == IND_CODE || cw->cod.arg.v2 == DIR_CODE)
		cw->car[i_car]->reg[IN(cw->arg[2])] |= code_to_byte(cw->map, cw->arg[1],\
			(cw->cod.arg.v2 == IND_CODE) ? IND_SIZE : cw->op[OR].label_size);
	else
		cw->car[i_car]->reg[IN(cw->arg[2])] |= cw->car[i_car]->reg[IN(cw->arg[1])];
	cw->car[i_car]->carry = (cw->car[i_car]->reg[IN(cw->arg[2])]) ? 0 : 1;
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	if (cw->f.lg.vs & VISU)
		vs_log(cw, i_car, 0);
}
