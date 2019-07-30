/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:06:10 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/30 15:49:52 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void			op_ld(t_cw *cw, size_t i_car)
{
	if (cw_codage_validator(cw, i_car, LD))
		return ;
	cw->pos = cw_code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	if (cw->arg[1] > 0x1 ||\
		(cw->arg[1] == 0x1 && 1 <= -cw->pos && -cw->pos <= cw->num_of_champs))
	{
		cw->car[i_car]->reg[IN(cw->arg[1])] = cw->pos;
		cw->car[i_car]->carry = (cw->pos) ? 0 : 1;
	}
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
