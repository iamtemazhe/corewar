/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:07:08 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/31 15:38:51 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void			op_sti(t_cw *cw, size_t i_car)
{
	if (cw_codage_validator(cw, i_car, STI))
		return ;
	cw->arg[1] = (cw->cod.arg.v2 == REG_CODE) ?\
				cw->car[i_car]->reg[cw->arg[1]] : cw->arg[1];
	cw->arg[2] = (cw->cod.arg.v3 == REG_CODE) ?\
				cw->car[i_car]->reg[cw->arg[2]] : cw->arg[2];
	cw->pos = PCV((cw->arg[1] + cw->arg[2]) % IDX_MOD + cw->car[i_car]->pc);
	cw_byte_to_code(cw->map, cw->pos,\
					&cw->car[i_car]->reg[cw->arg[0]], REG_SIZE);
	if (cw->f.lg.vs)
		vs_log(cw, i_car, 0, cw->pos);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
