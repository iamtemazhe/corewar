#include "cw.h"

void				op_aff(t_cw *cw, size_t i_car)
{
	uint8_t			letter;
	static int32_t	pos = 0;

	if (codage_validator(cw, i_car, AFF) || !cw->f.lg.af)
		return ;
		pos = 0;
	letter = (char)cw->car[i_car]->reg[IN(cw->arg[0])];
	// if (cw->f.lg.vs)
	// {
	// 	if (!pos)
	// 		mvwprintw(cw->vs.aff, 1, 1, "AFF: ");
	// 	mvwprintw(cw->vs.aff, 1, 6 + pos++, "%c", letter);
	// }
	// else 
		write(1, &letter, 1);
}
