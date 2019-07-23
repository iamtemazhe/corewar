#include "cw.h"

void			op_sti(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, STI))
		return ;
	cw->pos = (cw->cod.arg.v2 == REG_CODE) ? cw->car[i_car]->reg[IN(cw->arg[1])] :\
				(int16_t)code_to_byte(cw->map, cw->arg[1], REG_SIZE);
	cw->pos += (cw->cod.arg.v3 == REG_CODE) ? cw->car[i_car]->reg[IN(cw->arg[2])] :\
				(int16_t)code_to_byte(cw->map, cw->arg[2], REG_SIZE);
	cw->pos = PCV(cw->pos % IDX_MOD + cw->car[i_car]->pc);
	byte_to_code(cw->map, cw->pos, &cw->car[i_car]->reg[IN(cw->arg[0])], REG_SIZE);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	if (cw->f.lg.vs)
		vs_log(cw, i_car, cw->pos);
}
