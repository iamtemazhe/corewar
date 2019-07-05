#include "cw.h"

void			op_fork(t_cw *cw, uint8_t i_car)
{
	add_car(cw, i_car);
	cw->car[cw->num_of_cars - 1]->reg[0] = cw->champ[i_car].id;
	cw->car[cw->num_of_cars - 1]->cycle_to_wait = cw->op[FORK].cycles;
	cw->car[cw->num_of_cars - 1]->pc = PC_INC(cw->arg[0] % IDX_MOD + cw->car[i_car]->pc, 0);
	cw->car[i_car]->pc = PC_INC(cw->car[i_car]->pc, OP_SIZE + DIR_SIZE);
	vs_log(cw, FORK);
}
