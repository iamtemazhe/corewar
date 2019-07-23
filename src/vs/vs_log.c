/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:10:38 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/23 22:29:32 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void				vs_log(t_cw *cw, size_t i_car, int32_t pc)
{
	cw->visu.st_op = st_add(cw, i_car, pc, cw->visu.st_op);
	cw->map[pc].v.bold = CYCLE_TO_SHOW;
	if (cw->car[i_car]->op_code == cw->op[LIVE].code)
	{
		cw->map[pc].v.live = 1;
		cw->f.lg.vs_live = 1;
	}
	vs_backlight_map(cw, cw->visu.st_op, 1);
}

static void		vs_backlightoff_map(t_cw *cw, int32_t pc)
{
	if (pc > 0 && cw->map[pc - 1].v.col != cw->map[pc].v.col)
		wattron(cw->visu.map, COLOR_PAIR(cw->map[pc].v.col * 2 - 1));
	mvwprintw(cw->visu.map, VPCY(pc), VPCX(pc), "%.2x", cw->map[pc].v.code);
}

void				vs_map(t_cw *cw)
{
	int32_t			pc;

	pc = -1;
	wattron(cw->visu.map, COLOR_PAIR(cw->map[0].v.col * 2 - 1));
	while (++pc < MEM_SIZE)
		if (cw->map[pc].v.bold)
			if (!(--cw->map[pc].v.bold))
			{
				if (cw->map[pc].v.live)
					cw->map[pc].v.live = 0;
				vs_backlightoff_map(cw, pc);
			}
}

void				print_live_breakdown(t_cw *cw, int mod)
{
	uint			k;
	uint			i;
	uint			j;
	uint			total;

	k = (mod < 0) ? 11 + 4 * cw->num_of_champs : 13 + 4 * cw->num_of_champs;
	wattron(cw->visu.header, COLOR_PAIR(15) | A_BOLD);
	i = 0;
	total = 0;
	while (i < cw->num_of_champs)
		total = total + cw->champ[i++]->lives;
	i = 1;
	j = 0;
	total = (!total) ? cw->num_of_champs : total;
	mvwprintw(cw->visu.header, k, i, "[");
	while (++i < 50)
	{
		if (i < 48 / total * (3 + cw->champ[j]->lives))
			wattron(cw->visu.header, COLOR_PAIR(j++ * 2 + 1) | A_BOLD);
		mvwprintw(cw->visu.header, k, i, "-");
	}
	wattron(cw->visu.header, COLOR_PAIR(15) | A_BOLD);
	mvwprintw(cw->visu.header, k, i, "]");
	wrefresh(cw->visu.header);
}
