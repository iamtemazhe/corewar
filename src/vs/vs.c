/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/28 20:04:09 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

static void		vs_map(t_cw *cw)
{
	int32_t		pc;
	uint8_t		col;

	col = 0;
	pc = -1;
	while (++pc < MEM_SIZE)
		if (cw->map[pc].v.bold)
			if (!(--cw->map[pc].v.bold))
			{
				if (cw->map[pc].v.live)
					cw->map[pc].v.live = 0;
				if (cw->map[pc].v.car)
					wattron(cw->vs.map, COLOR_PAIR((col = cw->map[pc].v.col + COL_STEP)));
				else if (col != cw->map[pc].v.col)
					wattron(cw->vs.map, COLOR_PAIR(cw->map[pc].v.col));
				mvwprintw(cw->vs.map, VPCY(pc), VPCX(pc), "%02x",\
												cw->map[pc].v.code);
			}
}

static void		select_key(t_cw *cw, int key)
{
	if (key == 'q' && cw->vs.delay <= 95)
		cw->vs.delay += 5;
	else if (key == 'w' && cw->vs.delay < 100)
		cw->vs.delay++;
	else if (key == 'r' && cw->vs.delay >= 5)
		cw->vs.delay -= 5;
	else if (key == 'e' && cw->vs.delay >= 1)
		cw->vs.delay--;
	else if (key == 'a')
		cw->f.lg.vs_audio = (cw->f.lg.vs_audio) ? 0 : 1;
	mvwprintw(cw->vs.header, 3, 23, "%-4u", 1000 - (cw->vs.delay * 10));
	wrefresh(cw->vs.header);
	wtimeout(cw->vs.bkg, cw->vs.delay);
}

static void		wait_key(t_cw *cw)
{
	int			key;
	uint8_t		prnt;

	prnt = 1;
	while (1)
		if ((key = wgetch(cw->vs.bkg)) == 27)
			vs_exit(cw);
		else if (key == 32 || (key == 's' && !cw->f.lg.vs_pause))
			cw->f.lg.vs_pause =\
				(key == 's' || (key == 32 && !cw->f.lg.vs_pause)) ? 1 : 0;
		else if (key == 'q' || key == 'w' || key == 'e' || key == 'r')
			select_key(cw, key);
		else if (!cw->f.lg.vs_pause || key == 's')
		{
			mvwprintw(cw->vs.header, 1, 1, "%s", "** RUNNIG **");
			break ;
		}
		else if (cw->f.lg.vs_pause && prnt--)
		{
			mvwprintw(cw->vs.header, 1, 1, "%s", "** PAUSED **");
			wrefresh(cw->vs.header);
		}
}

void			vs_out(t_cw *cw)
{
	uint8_t		raw;

	raw = 11 + 4 * cw->num_of_champs;
	vs_map(cw);
	wnoutrefresh(cw->vs.map);
	mvwprintw(cw->vs.header, 8, 13, "%-7u", cw->num_of_cars);
	mvwprintw(cw->vs.header, raw + 14, 1, "The winner is : ");
	mvwprintw(cw->vs.header, raw + 16, 1, "Press any key to exit");
	wattroff(cw->vs.header, A_BOLD);
	mvwprintw(cw->vs.header, raw, 1, "%s",\
		"[--------------------------------------------------]");
	mvwprintw(cw->vs.header, raw + 3, 1, "%s",\
		"[--------------------------------------------------]");	
	wattron(cw->vs.header, COLOR_PAIR(cw->last_live_id) | A_BOLD);
	mvwprintw(cw->vs.header, raw + 14, 17, "%s", cw->champ[cw->last_live_id - 1]->head.prog_name);
	wnoutrefresh(cw->vs.header);
	doupdate();
	while (wgetch(cw->vs.bkg) == ERR)
		sleep(1);
	vs_exit(cw);
}

void			vs(t_cw *cw)
{
	vs_map(cw);
	mvwprintw(cw->vs.header, 6, 9, "%-7u", cw->cycles);
	if (cw->f.lg.vs_live)
		vs_print_lives(cw, 0);
	if (cw->start_cycle > cw->cycles)
		return ;
	wnoutrefresh(cw->vs.map);
	wait_key(cw);
	wrefresh(cw->vs.header);
}
