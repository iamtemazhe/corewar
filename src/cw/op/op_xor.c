/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:07:32 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/30 15:33:55 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void			op_xor(t_cw *cw, size_t i_car)
{
	if (cw_codage_validator(cw, i_car, XOR))
		return ;
	cw->pos = (cw->cod.arg.v1 == REG_CODE) ?\
								cw->car[i_car]->reg[IN(cw->arg[0])] :\
								cw_code_to_byte(cw->map, cw->arg[0], REG_SIZE);
	cw->pos ^= (cw->cod.arg.v2 == REG_CODE) ?\
								cw->car[i_car]->reg[IN(cw->arg[1])] :\
								cw_code_to_byte(cw->map, cw->arg[1], REG_SIZE);
	if (cw->arg[2] > 0x1 || (cw->arg[2] == 0x1 && 1 <= -cw->pos && -cw->pos <= cw->num_of_champs))
	{
		cw->car[i_car]->reg[IN(cw->arg[2])] = cw->pos;
		cw->car[i_car]->carry = (cw->pos) ? 0 : 1;
	}
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
}
