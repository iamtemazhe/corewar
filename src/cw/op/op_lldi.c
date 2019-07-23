#include "cw.h"

void			op_lldi(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, LLDI))
		return ;
	cw->pos = (cw->cod.arg.v1 == REG_CODE) ? cw->car[i_car]->reg[IN(cw->arg[0])] :\
				(int16_t)code_to_byte(cw->map, cw->arg[0], cw->op[LLDI].label_size);
										// code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	cw->pos += (cw->cod.arg.v2 == REG_CODE) ? cw->car[i_car]->reg[IN(cw->arg[1])] :\
				(int16_t)code_to_byte(cw->map, cw->arg[0], cw->op[LLDI].label_size);
										// code_to_byte(cw->map, cw->arg[1], REG_SIZE);
	cw->pos = PCV(cw->pos + cw->car[i_car]->pc);
	cw->car[i_car]->reg[IN(cw->arg[2])] = code_to_byte(cw->map, cw->pos, REG_SIZE);
	cw->car[i_car]->carry = (cw->car[i_car]->reg[IN(cw->arg[2])]) ? 0 : 1;
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
