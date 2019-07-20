#include "cw.h"

void			op_ldi(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, LDI))
		return ;
	if (cw->cod.arg.v1 == IND_CODE || cw->cod.arg.v1 == DIR_CODE)
		cw->pos = code_to_byte(cw->map, cw->arg[0],\
			(cw->cod.arg.v1 == IND_CODE) ? IND_SIZE : cw->op[LDI].label_size);
	else
		cw->pos = cw->car[i_car]->reg[IN(cw->arg[1])];
	if (cw->cod.arg.v2 == DIR_CODE)
		cw->pos += code_to_byte(cw->map, cw->arg[1], cw->op[LDI].label_size);
	else
		cw->pos += cw->car[i_car]->reg[IN(cw->arg[1])];
	cw->pos = cw->pos % IDX_MOD + cw->car[i_car]->pc;
	cw->car[i_car]->reg[IN(cw->arg[2])] = code_to_byte(cw->map, cw->pos, REG_SIZE);
	cw->car[i_car]->carry = (cw->car[i_car]->reg[IN(cw->arg[2])]) ? 0 : 1;
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	if (cw->f.lg.vs)
		vs_log(cw, i_car, 0);
}
