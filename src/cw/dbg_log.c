/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:05:24 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/30 16:46:28 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

inline void			dbg_log_table(uint8_t mode)
{
	if (mode)
	{
		ft_printf("\033[0m%s%s",\
		"'----------------------------------------------",\
		"-----------------------------------------'\n\r");
	}
	else
	{
		ft_printf("\033[0m\033[2J%s%s%s%s%s%s",\
		",----------------------------------------------",\
		"-----------------------------------------,\n\r",\
		"|car id| pc |op name|code|  codage   |  arg1  |",\
		"  arg2  |  arg3  |param|val 1|val 2|val 3|\n\r",\
		"|------|----|-------|----|-----------|--------|",\
		"--------|--------|-----|-----|-----|-----|\n\r");
	}
}

static inline void	dbg_log_cycles(t_cw *cw)
{
	cw->f.lg.dbg_cm = 0;
	ft_printf("%38\033[37m|\033[1m%9s Cycle: %7zu%9\033[22m|\n\r",\
													"", cw->cycles);
}

void				dbg_log_cod(t_cw *cw, size_t i_car)
{
	if (cw->start_cycle > cw->cycles)
		return ;
	if (cw->f.lg.dbg_cm && cw->f.lg.dbg_c)
		dbg_log_cycles(cw);
	ft_printf("\033[3%1um|\033[1m%5u \033[22m|%4u|%6s | %02x |",\
					cw->car[i_car]->id % 6 + 1, cw->car[i_car]->id,\
					cw->car[i_car]->pc,\
					cw->op[IN(cw->car[i_car]->op_code)].name,\
											cw->car[i_car]->op_code);
	ft_printf("%02b %02b %02b %02b|%8x|%8x|%8x|%5s|%5d|%5d|%5d|\n\r",\
				cw->cod.arg.v1, cw->cod.arg.v2, cw->cod.arg.v3, cw->cod.arg.v4,\
				cw->arg_code[0], cw->arg_code[1], cw->arg_code[2],\
				(cw->err) ? "\033[1merror\033[22m" : "",\
				cw->arg[0], cw->arg[1], cw->arg[2]);
	ft_bzero(cw->arg, sizeof(*cw->arg) * OP_NUM_ARGS);
	ft_bzero(cw->arg_code, sizeof(*cw->arg_code) * OP_NUM_ARGS);
}

void				dbg_log(t_cw *cw, size_t i_car)
{
	if (cw->start_cycle > cw->cycles)
		return ;
	if (cw->f.lg.dbg_cm && cw->f.lg.dbg_c)
		dbg_log_cycles(cw);
	ft_printf("\033[3%1um|\033[1m%5u \033[22m|%4u|%6s | %02x |",
				cw->car[i_car]->id % 6 + 1, cw->car[i_car]->id,\
				cw->car[i_car]->pc,\
				cw->op[IN(cw->car[i_car]->op_code)].name,\
										cw->car[i_car]->op_code);
	ft_printf("%12|%8x|%9|%9|%5s|%5d|%6|%6|\n\r",
				cw->arg[0], (cw->err) ? "\033[1mcarry\033[22m" : "",\
											(int16_t)cw->arg[0]);
}
