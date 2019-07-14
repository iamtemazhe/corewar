#include "cw.h"

void			op_lfork(t_cw *cw, uint8_t i_car)
{
	uint8_t		id_car;

	if (cw->flg & DEBUG)
		debug_log(cw, i_car);
	// ft_printf(" | pc[%u] = %u, op_code = %#x, ", i_car, cw->car[i_car]->pc, cw->car[i_car]->op_code);
	id_car = add_car(cw, i_car);
	cw->step = OP_SIZE + cw->op[LFORK].label_size;
	cw->pos = code_to_byte(cw->map, cw->car[i_car]->pc + cw->step, cw->op[LFORK].label_size);
	cw->car[id_car]->pc = PCV(cw->car[i_car]->pc + cw->pos);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	if (cw->flg & VISU)
		vs_log(cw, i_car);
}
