#include "cw.h"

void			op_sti(t_cw *cw, uint8_t i_car)
{
	if (codage_validator(cw, i_car, STI))
		return ;
	if (cw->cod.arg.v2 & IND_CODE || cw->cod.arg.v2 & DIR_CODE)
		cw->pos = code_to_byte(cw->map, cw->arg[1],\
			(cw->cod.arg.v2 & IND_CODE) ? IND_SIZE : cw->op[STI].label_size);
	else
		cw->pos = cw->car[i_car]->reg[cw->arg[1]];
	if (cw->cod.arg.v3 & DIR_CODE)
		cw->pos += code_to_byte(cw->map, cw->arg[2], cw->op[STI].label_size);
	else
		cw->pos += cw->car[i_car]->reg[cw->arg[2]];
	ft_printf("\n\r pos_do = %u, arg1 = %u, arg2 = %u,", cw->pos, cw->arg[1], cw->arg[2]);
	cw->pos = cw->pos % IDX_MOD + cw->car[i_car]->pc;
	ft_printf("\n\r pos_posle = %u, reg = %d\n\r", cw->pos, cw->car[i_car]->reg[cw->arg[0]]);
	byte_to_code(cw->map, cw->pos, &cw->car[i_car]->reg[cw->arg[0]], REG_SIZE);
	cw->car[i_car]->pc = PC_INC(cw->car[i_car]->pc, cw->step);
	vs_log(cw, STI);
}
