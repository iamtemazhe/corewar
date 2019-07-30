/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:05:48 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/30 15:47:41 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void				op_aff(t_cw *cw, size_t i_car)
{
	uint8_t			letter;
	static int32_t	col = 0;
	static int32_t	raw = 0;

	if (cw_codage_validator(cw, i_car, AFF) || !cw->f.lg.af)
		return ;
	letter = (char)cw->car[i_car]->reg[IN(cw->arg[0])];
	if (cw->f.lg.vs)
	{
		mvwprintw(cw->vs.aff, raw, col += 2, "%c ", letter);
		if (!(col % 254))
		{
			raw++;
			col = 0;
		}
		wnoutrefresh(cw->vs.aff);
	}
	else
		ft_printf("Aff: %c\n", letter);
}
