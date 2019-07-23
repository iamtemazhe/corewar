#include "cw.h"

void			op_ldi(t_cw *cw, size_t i_car)
{
	if (codage_validator(cw, i_car, LDI))
		return ;
	cw->pos = (cw->cod.arg.v1 == REG_CODE) ? cw->car[i_car]->reg[IN(cw->arg[0])] :\
				(int16_t)code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	if (cw->f.lg.dbg)
		ft_printf("pos1 = %x, ", cw->pos);
	cw->pos += (cw->cod.arg.v2 == REG_CODE) ? cw->car[i_car]->reg[IN(cw->arg[1])] :\
				(int16_t)code_to_byte(cw->map, cw->arg[1], REG_SIZE);
	if (cw->f.lg.dbg)
		ft_printf("pos2 = %x, ", cw->pos);
	cw->pos = PCV(cw->pos % IDX_MOD + cw->car[i_car]->pc + REG_SIZE);
	if (cw->f.lg.dbg)
		ft_printf("pos_res = %d, ", cw->pos);
	cw->car[i_car]->reg[IN(cw->arg[2])] = code_to_byte(cw->map, cw->pos, REG_SIZE);
	if (cw->f.lg.dbg)
		ft_printf("reg = %08x\n\r", cw->car[i_car]->reg[IN(cw->arg[2])]);
	cw->car[i_car]->carry = (cw->car[i_car]->reg[IN(cw->arg[2])]) ? 0 : 1;
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
