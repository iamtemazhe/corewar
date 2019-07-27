#include "cw.h"

void			op_aff(t_cw *cw, size_t i_car)
{
	uint8_t		letter;

	if (codage_validator(cw, i_car, ST) || !cw->f.lg.af)
		return ;
	letter = cw->car[i_car]->reg[IN(cw->arg[0])] % 0xFF;
	write(1, &letter, 1);
}
