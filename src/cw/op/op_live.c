#include "cw.h"

void			op_live(t_cw *cw, size_t i_car)
{
	uint8_t		id_champ;
	int16_t		i;
	uint32_t	id;

	cw->car[i_car]->last_live = cw->cycles + 1;
	cw->step = OP_SIZE + cw->op[LIVE].label_size;
	cw->pos = PCV(cw->car[i_car]->pc + cw->step);
	cw->arg[0] = code_to_byte(cw->map, cw->pos, cw->op[LIVE].label_size);
	id = -cw->arg[0];
	id_champ = -cw->car[i_car]->reg[0];
	if (1 <= id && id <= MAX_PLAYERS)
	{
		i = -1;
		// while (++i < cw->num_of_champs)
			// if (id == cw->champ[i]->id)
			if (id == id_champ)
			{
				cw->lives++;
				cw->champ[id_champ - 1]->lives++;
				cw->champ[id_champ - 1]->last_live = cw->cycles + 1;
				cw->last_live_id = id;
				if (cw->f.lg.vs)
					vs_log(cw, i_car, cw->car[i_car]->pc);
				// break ;
			}
	}
	if (cw->f.lg.dbg || cw->f.lg.vs)
		(cw->f.lg.dbg) ? dbg_log(cw, i_car) :\
								vs_backlight_car(cw, i_car, cw->step, 1);
	cw->car[i_car]->pc = cw->pos;
}
