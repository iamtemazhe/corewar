/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:06:01 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/30 15:33:55 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void			op_fork(t_cw *cw, size_t i_car)
{
	cw->step = OP_SIZE + cw->op[FORK].label_size;
	cw->arg[0] = (int16_t)cw_code_to_byte(cw->map,\
				cw->car[i_car]->pc + cw->step, cw->op[FORK].label_size);
	add_car(cw, i_car, PCV(cw->arg[0] % IDX_MOD + cw->car[i_car]->pc));
	if (cw->f.lg.vs)
		vs_backlight_car(cw, i_car, cw->step, 1);
	else if (cw->f.lg.dbg)
		dbg_log(cw, i_car);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
