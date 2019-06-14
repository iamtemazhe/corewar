#include "cw.h"
#include "libft.h"

void			op_live(t_cw *cw, uint32_t i)
{
	uint32_t	id;

	cw->lives++;
	cw->car[i].last_live = cw->cycles;
	id = -(uint32_t)cw->map[cw->car[i].PC + OPI_SIZE + cw->op[LIVE].label_size];
	cw->car[i].PC += cw->op[LIVE].label_size + OP_SIZE;
	if (1 <= id && id <= cw->num_of_champs)
		cw->champ[id - 1].lives++;
}
