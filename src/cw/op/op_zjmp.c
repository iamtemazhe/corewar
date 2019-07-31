/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:07:38 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/31 15:14:15 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void			op_zjmp(t_cw *cw, size_t i_car)
{
	cw->step = OP_SIZE + cw->op[ZJMP].label_size;
	cw->arg[0] = cw_code_to_byte(cw->map,\
					cw->car[i_car]->pc + cw->step, cw->op[ZJMP].label_size);
	cw->err = (cw->car[i_car]->carry) ? 0 : -1;
	cw->step = (cw->car[i_car]->carry) ? cw->arg[0] % IDX_MOD : cw->step;
	if (cw->f.lg.vs)
		vs_backlight_car(cw, i_car, cw->step, 1);
	else if (cw->f.lg.dbg)
		dbg_log(cw, i_car);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	cw->err = 0;
}
