/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:10:38 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/13 19:44:36 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void			vs_log(t_cw *cw, uint8_t i_car)
{
	uint8_t		col;
	uint8_t		i_op;
	int			x;
	int			y;

	i_op = IN(cw->car[i_car]->op_code);
	if (i_op)
		col = 0;
	col = (uint8_t)cw->car[i_car]->reg[0] + 1;
	getmaxyx(cw->visu.map,y,x);
	// ft_printf("%s, ", cw->op[i_op].name);
	wattron(cw->visu.map, COLOR_PAIR(col) | A_BOLD);
	mvwprintw(cw->visu.map, cw->car[i_car]->pc * 3 / x + 1, cw->car[i_car]->pc * 3 % x + 1, "%.2x", cw->map[cw->car[i_car]->pc]);
	wrefresh(cw->visu.map);
}
