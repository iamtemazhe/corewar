/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:07:04 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/31 16:05:29 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void			op_st(t_cw *cw, size_t i_car)
{
	if (cw_codage_validator(cw, i_car, ST))
		return ;
	if (cw->cod.arg.v2 == IND_CODE)
		cw_byte_to_code(cw->map, cw->arg[1],\
			&cw->car[i_car]->reg[cw->arg[0]], REG_SIZE);
	else
	{
		cw->pos = cw->car[i_car]->reg[cw->arg[0]];
		if (cw->arg[1] ||\
				(1 <= -cw->pos && -cw->pos <= cw->num_of_champs))
			cw->car[i_car]->reg[cw->arg[1]] = cw->pos;
	}
	if (cw->f.lg.vs && cw->cod.arg.v2 == IND_CODE)
		vs_log(cw, i_car, 0, cw->arg[1]);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
