#include "cw.h"

void			op_fork(t_cw *cw, uint8_t i_car)
{
	uint8_t		id_car;

	// ft_printf(" | pc[%u] = %u, op_code = %#x, ", i_car, cw->car[i_car]->pc, cw->car[i_car]->op_code);
	id_car = add_car(cw, i_car);
	cw->step = OP_SIZE + cw->op[FORK].label_size;
	cw->pos = code_to_byte(cw->map, cw->car[i_car]->pc + cw->step, cw->op[FORK].label_size);
	cw->car[id_car]->pc = PCV(cw->car[i_car]->pc + cw->pos % IDX_MOD);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	vs_log(cw, FORK, i_car);
}
