#include "cw.h"

void			op_lld(t_cw *cw, uint8_t i_car)
{
	if (codage_validator(cw, i_car, LLD))
		return ;
	if (cw->cod.arg.v1 & IND_CODE)
	{
		cw->pos = cw->car[i_car]->pc + OPC_SIZE + IND_SIZE;
		cw->arg[0] = code_to_byte(cw->map, cw->pos, REG_SIZE) + cw->car[i_car]->pc;
	}
	cw->car[i_car]->reg[cw->arg[1]] = code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	cw->car[i_car]->carry = (cw->car[i_car]->reg[cw->arg[1]]) ? 0 : 1;
	cw->car[i_car]->pc = PC_INC(cw->car[i_car]->pc, cw->step);
	vs_log(cw, LLD);
}
