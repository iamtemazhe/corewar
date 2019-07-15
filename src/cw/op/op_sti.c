#include "cw.h"

void			op_sti(t_cw *cw, uint8_t i_car)
{
	if (codage_validator(cw, i_car, STI))
		return ;
	if (cw->cod.arg.v2 == IND_CODE || cw->cod.arg.v2 == DIR_CODE)
		cw->pos = code_to_byte(cw->map, cw->arg[1],\
			(cw->cod.arg.v2 == IND_CODE) ? IND_SIZE : cw->op[STI].label_size);
	else
		cw->pos = cw->car[i_car]->reg[IN(cw->arg[1])];
	if (cw->cod.arg.v3 == DIR_CODE)
		cw->pos += code_to_byte(cw->map, cw->arg[2], cw->op[STI].label_size);
	else
		cw->pos += cw->car[i_car]->reg[IN(cw->arg[2])];
	cw->pos = cw->pos % IDX_MOD + cw->car[i_car]->pc;
	byte_to_code(cw->map, cw->pos, &cw->car[i_car]->reg[IN(cw->arg[0])], REG_SIZE);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	if (cw->flg & VISU)
		vs_log(cw, i_car, STI);
}
