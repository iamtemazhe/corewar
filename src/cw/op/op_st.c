#include "cw.h"

void			op_st(t_cw *cw, uint8_t i_car)
{
	if (codage_validator(cw, i_car, ST))
		return ;
	// ft_printf(" ind_pos = %u, val_pos = %#x, ", cw->arg[1], cw->map[PC(cw->arg[1])]);
	if (cw->cod.arg.v2 == IND_CODE)
		byte_to_code(cw->map, cw->arg[1], &cw->car[i_car]->reg[cw->arg[0]], REG_SIZE);
	else
		cw->car[i_car]->reg[cw->arg[1]] = cw->car[i_car]->reg[cw->arg[0]];
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	if (cw->flg & VISU)
		vs_log(cw, i_car);
}
