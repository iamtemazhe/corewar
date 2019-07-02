#include "cw.h"

void			op_lfork(t_cw *cw, uint8_t i_car)
{
	add_car(cw, i_car);
	cw->car[cw->num_of_cars - 1].reg[0]= cw->champ[i_car].id;
	cw->car[cw->num_of_cars - 1].cycle_to_wait = cw->op[LFORK].cycles;
	cw->car[cw->num_of_cars - 1].pc = PC(cw->arg[0] + cw->car[i_car].pc);
	cw->car[i_car].pc += OP_SIZE + DIR_SIZE;
	vs_log(cw, LFORK);
}
