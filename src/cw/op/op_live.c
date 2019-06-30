#include "cw.h"

void			op_live(t_cw *cw, uint8_t i_car)
{
	cw->lives++;
	cw->car[i_car].last_live = cw->cycles;
	cw->pos = cw->car[i_car].pc + OP_SIZE + cw->op[LIVE].label_size;
	cw->car[i_car].pc = cw->pos;
	cw->pos = -code_to_byte(cw->map, cw->pos, cw->op[LIVE].label_size);
	if (1 <= cw->pos && cw->pos <= cw->num_of_champs)
		cw->champ[IN(cw->pos)].lives++;
}