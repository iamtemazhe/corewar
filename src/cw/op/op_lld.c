#include "cw.h"

void			op_lld(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, LLD))
		return ;
	if (cw->cod.arg.v1 == IND_CODE)
	{
		cw->pos = cw->car[i_car]->pc + OPC_SIZE + IND_SIZE;
		cw->arg[0] = PCV((int16_t)code_to_byte(cw->map, cw->pos, IND_SIZE) + cw->car[i_car]->pc);
	}
	cw->pos = code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	if (cw->arg[1] > 0x1 || (cw->arg[1] == 0x1 && 1 <= -cw->pos && -cw->pos <= cw->num_of_champs))
	{
		cw->car[i_car]->reg[IN(cw->arg[1])] = cw->pos;
		cw->car[i_car]->carry = (cw->pos) ? 0 : 1;
	}
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
