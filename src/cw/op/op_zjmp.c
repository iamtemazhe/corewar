#include "cw.h"

void			op_zjmp(t_cw *cw, uint8_t i_car)
{
	// if (cw->flg & DEBUG)
		// dbg_log(cw, i_car);
	if (!cw->car[i_car]->carry)
		return ;
	// ft_printf("\n\rpc[%u] = %u, op_code = %#x, ", i_car, cw->car[i_car]->pc, cw->car[i_car]->op_code);
	cw->step = OP_SIZE + cw->op[ZJMP].label_size;
	cw->pos = code_to_byte(cw->map, cw->car[i_car]->pc + cw->step, cw->op[ZJMP].label_size);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->pos % IDX_MOD);
	// ft_printf("new_pc[%u] = %u, ", i_car, cw->car[i_car]->pc);
	if (cw->flg & VISU)
		vs_log(cw, i_car);
}
