#include "cw.h"

void			op_live(t_cw *cw, size_t i_car)
{
	cw->lives++;
	cw->car[i_car]->last_live = cw->cycles;
	cw->pos = PCV(cw->car[i_car]->pc + OP_SIZE + cw->op[LIVE].label_size);
	cw->arg[0] = code_to_byte(cw->map, cw->pos, cw->op[LIVE].label_size);
	if (cw->f.lg.dbg)
		dbg_log(cw, i_car);
	if (1 <= cw->arg[0] && cw->arg[0] <= cw->num_of_champs)
		cw->champ[IN(cw->arg[0])]->lives++;
	if (cw->f.lg.vs)
		vs_log(cw, i_car, LIVE + 1);
	cw->car[i_car]->pc = cw->pos;
}
