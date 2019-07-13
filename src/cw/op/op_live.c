#include "cw.h"

void			op_live(t_cw *cw, uint8_t i_car)
{
	uint32_t	id_champ;

	cw->lives++;
	cw->car[i_car]->last_live = cw->cycles;

	// ft_printf("\n\r cw->pc = %u, ", cw->car[i_car]->pc);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + OP_SIZE + cw->op[LIVE].label_size);
	cw->pos = cw->car[i_car]->pc;
	// ft_printf("cw->pc + step = %u, ", cw->car[i_car]->pc);
	id_champ = code_to_byte(cw->map, cw->pos, cw->op[LIVE].label_size);
	ft_printf(" | pc[%u] = %u, op_code = %#x, id = %x", i_car, cw->car[i_car]->pc, cw->car[i_car]->op_code, id_champ);
	// ft_printf("id_champ = %#x\n\r", id_champ);
	if (1 <= id_champ && id_champ <= cw->num_of_champs)
		cw->champ[IN(id_champ)].lives++;
	vs_log(cw, LIVE, i_car);
}
