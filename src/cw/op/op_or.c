#include "cw.h"

void			op_or(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, OR))
		return ;
	cw->pos = (cw->cod.arg.v1 == REG_CODE) ?\
								cw->car[i_car]->reg[IN(cw->arg[0])] :\
								code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	cw->pos |= (cw->cod.arg.v2 == REG_CODE) ?\
								cw->car[i_car]->reg[IN(cw->arg[1])] :\
								code_to_byte(cw->map, cw->arg[1], REG_SIZE);
	if (cw->arg[2] > 0x1 || (cw->arg[2] == 0x1 && 1 <= -cw->pos && -cw->pos <= cw->num_of_champs))
	{
		cw->car[i_car]->reg[IN(cw->arg[2])] = cw->pos;
		cw->car[i_car]->carry = (cw->pos) ? 0 : 1;
	}
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
