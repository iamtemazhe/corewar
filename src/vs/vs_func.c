/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:45:08 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/31 19:05:29 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "libft.h"
#include <ncurses.h>

void		vs_backlight_on_car(t_cw *cw, uint8_t col, int32_t pc, uint8_t mode)
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
	mvwprintw(cw->vs.map, VPCY(pc), VPCX(pc), "%02x", cw->map[pc].v.code);
	wattroff(cw->vs.map, A_BOLD);
	if (mode)
		mvwprintw(cw->vs.header, 8, 13, "%-7u", cw->num_of_cars);
}

void		vs_backlight_car(t_cw *cw, size_t i_car, int32_t step, uint8_t mode)
{
	int32_t	pc;

	pc = cw->car[i_car]->pc;
	if (!(--cw->map[pc].v.car))
	{
		wattron(cw->vs.map, COLOR_PAIR(cw->map[pc].v.col +\
						((cw->map[pc].v.live) ? COL_LIVE_STEP : 0)));
		if (cw->map[pc].v.bold)
			wattron(cw->vs.map, A_BOLD);
		mvwprintw(cw->vs.map, VPCY(pc), VPCX(pc), "%02x",\
												cw->map[pc].v.code);
		if (cw->map[pc].v.bold && !mode)
			wattroff(cw->vs.map, A_BOLD);
	}
	if (mode)
		vs_backlight_on_car(cw, -cw->car[i_car]->reg[0], PCV(pc + step), 0);
}

void		vs_log(t_cw *cw, size_t i_car, uint8_t i_champ, int32_t pc)
{
	uint8_t	i;
	uint8_t	id;

	if (cw->car[i_car]->op_code == cw->op[LIVE].code)
	{
		cw->vs.champs_lives++;
		cw->map[pc].v.bold = CYCLE_TO_SHOW;
		cw->map[pc].v.live = 1;
		cw->f.lg.vs_live = 1;
		cw->champ[i_champ]->flg_live = 1;
		return ;
	}
	i = 0;
	id = -cw->car[i_car]->reg[0];
	while (++i <= REG_SIZE)
	{
		wattron(cw->vs.map, (cw->map[pc].v.car) ?\
					COLOR_PAIR(id + COL_STEP) : COLOR_PAIR(id) | A_BOLD);
		mvwprintw(cw->vs.map, VPCY(pc), VPCX(pc), "%02x", cw->map[pc].v.code);
		cw->map[pc].v.col = id;
		cw->map[pc].v.bold = CYCLE_TO_SHOW;
		pc = PCV(pc + 1);
	}
	wattroff(cw->vs.map, A_BOLD);
}

void		vs_checker(t_cw *cw, uint8_t mode)
{
	uint8_t	i_champ;

	i_champ = cw->num_of_champs;
	if (mode)
	{
		if (!cw->checks)
			mvwprintw(cw->vs.header, 16 + cw->num_of_champs * 4, 16, "%-7d",\
															cw->cycle_to_die);
		while (i_champ-- > 0)
		{
			cw->champ[i_champ]->lives = 0;
			mvwprintw(cw->vs.header, 12 + i_champ * 4, 31, "%7u",\
										cw->champ[i_champ]->lives);
		}
		return ;
	}
	while (i_champ-- > 0)
		if (cw->champ[i_champ]->flg_live)
		{
			mvwprintw(cw->vs.header, 11 + i_champ * 4, 31, "%7u",\
										cw->champ[i_champ]->last_live);
			mvwprintw(cw->vs.header, 12 + i_champ * 4, 31, "%7u",\
										cw->champ[i_champ]->lives);
			cw->champ[i_champ]->flg_live = 0;
		}
}

void		vs_print_lives(t_cw *cw, uint8_t mode)
{
	uint8_t	i_champ;
	uint8_t	raw;
	uint8_t	colum;
	uint8_t	lives;

	i_champ = 0;
	colum = 1;
	raw = (mode) ? 14 + cw->num_of_champs * 4 : 11 + cw->num_of_champs * 4;
	while (colum < 52)
	{
		lives = (cw->vs.champs_lives) ?\
			((cw->champ[i_champ]->lives * (LIVES_TO_SHOW + cw->num_of_champs))\
									/ cw->vs.champs_lives) : LIVES_TO_SHOW;
		wattron(cw->vs.header, COLOR_PAIR((cw->vs.champs_lives) ?\
									cw->champ[i_champ++]->id : COL_CODE));
		while (lives-- > 0 && ++colum < 52)
			mvwaddch(cw->vs.header, raw, colum, '-');
	}
	if (mode)
	{
		cw->vs.champs_lives = 0;
		vs_print_lives(cw, 0);
	}
	wattron(cw->vs.header, COLOR_PAIR(COL_TEXT) | A_BOLD);
	vs_checker(cw, 0);
}
