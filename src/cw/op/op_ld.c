#include "cw.h"

void			op_ld(t_cw *cw, uint8_t i_car)
{
	if (codage_validator(cw, i_car, LD))
		return ;
	cw->car[i_car].reg[cw->arg[1]] = code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	cw->car[i_car].carry = (cw->car[i_car].reg[cw->arg[1]]) ? 0 : 1;
	cw->car[i_car].pc += cw->step;
}