#include "cw.h"

void			op_lldi(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, LLDI))
		return ;
	cw->pos = (cw->cod.arg.v1 == REG_CODE) ? cw->car[i_car]->reg[IN(cw->arg[0])] :\
				(int16_t)code_to_byte(cw->map, cw->arg[0], cw->op[LLDI].label_size);
	cw->pos += (cw->cod.arg.v2 == REG_CODE) ? cw->car[i_car]->reg[IN(cw->arg[1])] :\
				(int16_t)code_to_byte(cw->map, cw->arg[1], cw->op[LLDI].label_size);
	cw->pos = PCV(cw->pos + cw->car[i_car]->pc);
	cw->pos = code_to_byte(cw->map, cw->pos, REG_SIZE);
	if (cw->arg[2] > 0x1 || (cw->arg[2] == 0x1 && 1 <= -cw->pos && -cw->pos <= cw->num_of_champs))
	{
		cw->car[i_car]->reg[IN(cw->arg[2])] = cw->pos;
		cw->car[i_car]->carry = (cw->car[i_car]->reg[IN(cw->arg[2])]) ? 0 : 1;
	}
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
