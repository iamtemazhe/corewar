#include "cw.h"

void			op_live(t_cw *cw, size_t i_car)
{
	int			i;

	cw->lives++;
	cw->car[i_car]->last_live = cw->cycles;
	cw->step = OP_SIZE + cw->op[LIVE].label_size;
	cw->pos = PCV(cw->car[i_car]->pc + cw->step);
	cw->arg[0] = code_to_byte(cw->map, cw->pos, cw->op[LIVE].label_size);
	if (1 <= cw->arg[0] && cw->arg[0] <= cw->num_of_champs)
	{
		i = -1;
		while (++i < cw->num_of_champs)
			if (cw->arg[0] == cw->champ[i]->id)
			{
				cw->champ[i]->last_live = cw->cycles;
				cw->champ[i]->lives++;
				break ;
			}
	}
	if (cw->f.lg.dbg || cw->f.lg.vs)
		(cw->f.lg.dbg) ? dbg_log_cod(cw, i_car) : vs_backlight_car(cw, i_car, cw->step);
	if (cw->f.lg.vs)
		vs_log(cw, i_car, cw->car[i_car]->pc);
	cw->car[i_car]->pc = cw->pos;
}
