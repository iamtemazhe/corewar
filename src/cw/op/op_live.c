#include "cw.h"

void			op_live(t_cw *cw, uint8_t i_car)
{
	cw->lives++;
	cw->car[i_car]->last_live = cw->cycles;
	cw->pos = PCV(cw->car[i_car]->pc + OP_SIZE + cw->op[LIVE].label_size);
	cw->arg[0] = code_to_byte(cw->map, cw->pos, cw->op[LIVE].label_size);
	if (cw->flg & DEBUG)
		dbg_log(cw, i_car);
	if (1 <= cw->arg[0] && cw->arg[0] <= cw->num_of_champs)
		cw->champ[IN(cw->arg[0])].lives++;
	if (cw->flg & VISU)
		vs_log(cw, i_car, LIVE);
	cw->car[i_car]->pc = cw->pos;
}
