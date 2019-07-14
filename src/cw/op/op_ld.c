#include "cw.h"

void			op_ld(t_cw *cw, uint8_t i_car)
{
	if (codage_validator(cw, i_car, LD))
		return ;
	cw->car[i_car]->reg[cw->arg[1]] = code_to_byte(cw->map, cw->arg[0],\
			(cw->cod.arg.v1 == IND_CODE) ? IND_SIZE : cw->op[LD].label_size);
	cw->car[i_car]->carry = (cw->car[i_car]->reg[cw->arg[1]]) ? 0 : 1;
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	// ft_printf(" pc_new = %u, ", cw->car[i_car]->pc);
	vs_log(cw, LD, i_car);
}
