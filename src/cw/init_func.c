#include "op_tab.h"
#include "cw.h"
#include "libft.h"

void				init_cw(t_cw *cw)
{
	cw->champ = NULL;
	cw->car = NULL;
	cw->err = 0;
	cw->flg = 0;
	ft_bzero(cw->map, sizeof(*cw->map) * MEM_SIZE);
	ft_bzero(cw->arg, sizeof(*cw->arg) * OP_NUM_ARGS);
	ft_bzero(cw->arg_code, sizeof(*cw->arg_code) * OP_NUM_ARGS);
	cw->num_of_champs = 0;
	cw->lives = 0;
	cw->checks = 0;
	cw->cycles = 0;
	cw->cycle_to_die = CYCLE_TO_DIE;
	cw->cycle_to_dump = 0;
	cw->step = 0;
	cw->pos = 0;
	cw->op = g_op;
}
