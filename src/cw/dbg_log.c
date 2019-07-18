#include "cw.h"

inline void		dbg_log_top()
{
	ft_printf("%s,---------------------------------------------------------------------------------------,\n\r%s%s",
				"\033[0m\033[2J",
				"|car id| pc |op name|code|  codage   |  arg1  |  arg2  |  arg3  |param|val 1|val 2|val 3|\n\r",
		    	"|------|----|-------|----|-----------|--------|--------|--------|-----|-----|-----|-----|\n\r");
}

inline void		dbg_log_bot()
{
	ft_printf("\033[0m'---------------------------------------------------------------------------------------'\n\r");
}

inline void		dbg_log_cod(t_cw *cw, size_t i_car)
{
	ft_printf("\033[3%1um|\033[1m%5d \033[22m|%4u|%6s | %02x |%02b %02b %02b %02b|%8x|%8x|%8x|%5s|%5d|%5d|%5d|\n\r",
				cw->car[i_car]->id % 6 + 1, cw->car[i_car]->id, cw->car[i_car]->pc,
				cw->op[IN(cw->car[i_car]->op_code)].name, cw->car[i_car]->op_code,
				cw->cod.arg.v1, cw->cod.arg.v2, cw->cod.arg.v3, cw->cod.arg.v4,
				cw->arg_code[0], cw->arg_code[1], cw->arg_code[2], (cw->err) ? "\033[1merror\033[22m" : "",
				(int16_t)cw->arg[0], (int16_t)cw->arg[1], (int16_t)cw->arg[2]);
}

inline void		dbg_log(t_cw *cw, size_t i_car)
{
	ft_printf("\033[3%1um|\033[1m%5d \033[22m|%4u|%6s | %02x |%12|%8x|%9|%9|%5s|%5d|%6|%6|\n\r",
				cw->car[i_car]->id % 6 + 1, cw->car[i_car]->id, cw->car[i_car]->pc,
				cw->op[IN(cw->car[i_car]->op_code)].name, cw->car[i_car]->op_code, cw->arg[0],
				(cw->err) ? "\033[1mcarry\033[22m" : "", (int16_t)cw->arg[0]);
}