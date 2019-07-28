#include "cw.h"

void			op_live(t_cw *cw, size_t i_car)
{
	uint8_t		i_champ;

	cw->lives++;
	cw->car[i_car]->last_live = cw->cycles + 1;
	cw->step = OP_SIZE + cw->op[LIVE].label_size;
	cw->pos = PCV(cw->car[i_car]->pc + cw->step);
	cw->arg[0] = code_to_byte(cw->map, cw->pos, cw->op[LIVE].label_size);
	cw->arg_code[0] = -cw->arg[0];
	i_champ = cw->num_of_champs;
	if (1 <= cw->arg_code[0] && cw->arg_code[0] <= MAX_PLAYERS)
		while (i_champ-- > 0)
			if (cw->arg_code[0] == cw->champ[i_champ]->id)
			{
				cw->champ_lives++;
				cw->champ[i_champ]->lives++;
				cw->champ[i_champ]->last_live = cw->cycles + 1;
				cw->last_live_id = cw->arg_code[0];
				if (cw->f.lg.vs)
					vs_log(cw, i_car, i_champ, cw->car[i_car]->pc);
				break ;
			}
	if (cw->f.lg.vs)
		vs_backlight_car(cw, i_car, cw->step, 1);
	else if (cw->f.lg.dbg)
		dbg_log(cw, i_car);
	cw->car[i_car]->pc = cw->pos;
}
