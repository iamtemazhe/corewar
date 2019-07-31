/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:06:23 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/31 16:03:03 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void			op_lfork(t_cw *cw, size_t i_car)
{
	cw->step = OP_SIZE + cw->op[LFORK].label_size;
	cw->pos = PCV(cw->car[i_car]->pc + cw->step);
	cw->arg[0] = cw_code_to_byte(cw->map, cw->pos,\
									cw->op[LFORK].label_size);
	add_car(cw, i_car, PCV(cw->arg[0] + cw->car[i_car]->pc));
	if (cw->f.lg.vs)
		vs_backlight_car(cw, i_car, cw->step, 1);
	else if (cw->f.lg.dbg)
		dbg_log(cw, i_car);
	cw->car[i_car]->pc = cw->pos;
}
