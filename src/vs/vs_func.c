/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:45:08 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/24 22:21:04 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "libft.h"
#include <ncurses.h>

void			vs_backlight_on_car(t_cw *cw, uint8_t col, int32_t pc, uint8_t mod)
{
	cw->map[pc].v.car++;
	(cw->map[pc].v.bold) ? wattron(cw->vs.map, A_BOLD) :\
							wattroff(cw->vs.map, A_BOLD);
	if (cw->map[pc].v.live)
		wattron(cw->vs.map,\
			COLOR_PAIR(cw->map[pc].v.col + COL_LIVE_STEP + COL_STEP) | A_BOLD);
	else
		wattron(cw->vs.map, COLOR_PAIR(((cw->map[pc].v.col == COL_CODE) ?\
										col : cw->map[pc].v.col) + COL_STEP));
	mvwprintw(cw->vs.map, VPCY(pc), VPCX(pc), "%.2x", cw->map[pc].v.code);
	wattroff(cw->vs.map, A_BOLD);
	if (mod)
		mvwprintw(cw->vs.header, 8, 13, "%-6d", cw->num_of_cars);
}

void			vs_backlight_car(t_cw *cw, size_t i_car, int32_t step, uint8_t mod)
{
	int32_t		pc;

	pc = cw->car[i_car]->pc;
	if (!(--cw->map[pc].v.car))
	{
		wattron(cw->vs.map, COLOR_PAIR(cw->map[pc].v.col +\
						((cw->map[pc].v.live) ? COL_LIVE_STEP : 0)));
		if (cw->map[pc].v.bold)
			wattron(cw->vs.map, A_BOLD);
		mvwprintw(cw->vs.map, VPCY(pc), VPCX(pc), "%.2x",\
												cw->map[pc].v.code);
		if (cw->map[pc].v.bold && !mod)
			wattroff(cw->vs.map, A_BOLD);
	}
	if (mod)
		vs_backlight_on_car(cw, -cw->car[i_car]->reg[0], PCV(pc + step), 0);
}

void			vs_log(t_cw *cw, size_t i_car, int32_t pc)
{
	uint8_t		i;
	uint8_t		id;

	id = -cw->car[i_car]->reg[0];
	if (cw->car[i_car]->op_code == cw->op[LIVE].code)
	{
		wattron(cw->vs.header, COLOR_PAIR(COL_TEXT) | A_BOLD);
		cw->map[pc].v.bold = CYCLE_TO_SHOW;
		cw->map[pc].v.live = 1;
		cw->f.lg.vs_live = 1;
		i = 7 + id * 4;
		mvwprintw(cw->vs.header, i++, 31, "%7u", cw->champ[IN(id)]->last_live);
		mvwprintw(cw->vs.header, i, 31, "%7u", cw->champ[IN(id)]->lives);
		return ;
	}
	i = 0;
	wattron(cw->vs.map, COLOR_PAIR(id) | A_BOLD);
	while (++i <= REG_SIZE)
	{
		mvwprintw(cw->vs.map, VPCY(pc), VPCX(pc), "%.2x",\
					cw->map[pc].v.code);
		cw->map[pc].v.col = id; 	
		cw->map[pc].v.bold = CYCLE_TO_SHOW;
		pc = PCV(pc + 1);
	}
	wattroff(cw->vs.map, A_BOLD);
}

void			vs_checker(t_cw *cw, uint8_t mod)
{
	uint8_t		i;
	uint8_t		raw;

	if (mod)
	{
		raw = cw->num_of_champs * 4 + 16;
		mvwprintw(cw->vs.header, raw, 16, "%-7u", cw->cycle_to_die);
		return ;
	}
	i = 0;
	raw = 8;
	while (i < cw->num_of_champs)
		mvwprintw(cw->vs.header, raw += 4 , 31, "%7u", cw->champ[i++]->lives);
}

void			vs_print_lives(t_cw *cw, uint8_t mod)
{
	uint8_t		i;
	uint8_t		raw;
	uint8_t		colum;
	uint8_t		lives;

	if (!cw->lives)
		return ;
	i = 0;
	lives = 0;
	colum = 1;
	raw = (mod) ? 14 + cw->num_of_champs * 4 : 11 + cw->num_of_champs * 4;
	while (i < cw->num_of_champs)
	{
		if ((lives = ((cw->champ[i]->lives / cw->lives) * LIVES_TO_SHOW)))
			wattron(cw->vs.header, COLOR_PAIR(cw->champ[i]->id));
		while (lives-- > 0 && ++colum < 52)
			mvwaddch(cw->vs.header, raw, colum, '-');
		i++;
	}
	wattron(cw->vs.header, COLOR_PAIR(COL_TEXT) | A_BOLD);
}
