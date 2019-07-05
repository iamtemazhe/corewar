#include "cw.h"

void			op_ldi(t_cw *cw, uint8_t i_car)
{
	if (codage_validator(cw, i_car, LDI))
		return ;
	if (cw->cod.arg.v1 & IND_CODE || cw->cod.arg.v1 & DIR_CODE)
		cw->pos = code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	else
		cw->pos = cw->car[i_car]->reg[cw->arg[1]];
	if (cw->cod.arg.v1 & DIR_CODE)
		cw->pos += code_to_byte(cw->map, cw->arg[1], REG_SIZE);
	else
		cw->pos += cw->car[i_car]->reg[cw->arg[1]];
	cw->pos = cw->pos % IDX_MOD + cw->car[i_car]->pc;
	cw->car[i_car]->reg[cw->arg[2]] = code_to_byte(cw->map, cw->pos, REG_SIZE);
	cw->car[i_car]->carry = (cw->car[i_car]->reg[cw->arg[2]]) ? 0 : 1;
	cw->car[i_car]->pc = PC_INC(cw->car[i_car]->pc, cw->step);
	vs_log(cw, LDI);
}
