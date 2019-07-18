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

static void		vs_log_live(t_cw *cw, uint8_t i_car)
{
	uint8_t		col;

	col = (uint8_t)cw->car[i_car]->reg[0] + 1;
}

static void		vs_log_st(t_cw *cw, uint8_t i_car)
{
	uint8_t		col;

	col = (uint8_t)cw->car[i_car]->reg[0] + 1;
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
	if (i_op)
		(i_op == LIVE) ? vs_log_live(cw, i_car) : vs_log_st(cw, i_car);
	wrefresh(cw->visu.map);
}