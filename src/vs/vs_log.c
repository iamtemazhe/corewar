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

static void				vs_log_op(t_cw *cw, uint8_t i_car, uint8_t i_op)
{
	if (1 <= i_op && i_op <= OP_NUM)
		cw->visu.st_op = st_add(cw->car[i_car]->pc, cw->cycles,
								(IN(i_op) == LIVE) ? OP_SIZE : REG_SIZE, cw->visu.st_op);
	while ((cw->visu.st_op = cw->visu.st_op->prev))
		if (cw->cycles - cw->visu.st_op->cycle_to_show >= CYCLE_TO_SHOW)
			st_del(&cw->visu.st_op);
		else
			break ;
}

void			vs_log(t_cw *cw, uint8_t i_car, uint8_t i_op)
{
	uint8_t		col;
	int			x;
	int			y;

	col = -cw->car[i_car]->reg[0];
	getmaxyx(cw->visu.map,y,x);
	wattron(cw->visu.map, COLOR_PAIR(col * 2) | A_BOLD);
	mvwprintw(cw->visu.map, cw->car[i_car]->pc * 3 / x + 1, cw->car[i_car]->pc * 3 % x + 1, "%.2x", cw->map[cw->car[i_car]->pc]);
	vs_log_op(cw, i_car, i_op);
	wrefresh(cw->visu.map);
}