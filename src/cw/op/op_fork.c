#include "cw.h"

void			op_fork(t_cw *cw, uint8_t i_car)
{
	add_car(cw, i_car);
	cw->car[cw->num_of_cars - 1]->reg[0] = cw->champ[i_car].id;
	cw->car[cw->num_of_cars - 1]->cycle_to_wait = cw->op[FORK].cycles;

	cw->pos = cw->car[i_car]->pc + OP_SIZE + cw->op[FORK].label_size;
	cw->car[i_car]->pc = PC_INC(cw->pos, 0);
	cw->pos = code_to_byte(cw->map, cw->pos, cw->op[FORK].label_size) % IDX_MOD;
	cw->car[cw->num_of_cars - 1]->pc = PC_INC(cw->pos, cw->car[i_car]->pc);
	vs_log(cw, FORK);
}
