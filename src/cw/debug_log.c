#include "cw.h"

inline void		debug_log_top()
{
	ft_printf(",-----------------------------------------------------,\n\r%s",
				"|cid| pc | name | codage |  arg1  |  arg2  |  arg3  | err |\n\r");
}

inline void		debug_log(t_cw *cw, uint8_t i_car)
{
	ft_printf("|%3d|%4u|%6s|%2b %2b %2b|%8x|%8x|%8x|%5s|\n\r", i_car, cw->car[i_car]->pc,
				cw->op[IN(cw->car[i_car]->op_code)].name, cw->cod.arg.v1,
				cw->cod.arg.v2, cw->cod.arg.v3, cw->arg[0], cw->arg[1], cw->arg[2],
				(cw->err) ? "true" : "false");
}

inline void		debug_log_bot()
{
	ft_printf("'-----------------------------------------------------'\n\r");
}