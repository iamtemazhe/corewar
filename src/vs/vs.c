/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/26 17:00:33 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

static void		vs_backlight_off_map(t_cw *cw, int32_t pc)
{
	if (cw->map[pc].v.car)
		wattron(cw->vs.map, COLOR_PAIR(cw->map[pc].v.col + COL_STEP));
	else if (pc > 0 && (cw->map[pc - 1].v.col != cw->map[pc].v.col ||\
												cw->map[pc - 1].v.car))
		wattron(cw->vs.map, COLOR_PAIR(cw->map[pc].v.col));
	mvwprintw(cw->vs.map, VPCY(pc), VPCX(pc), "%02x",\
												cw->map[pc].v.code);
}

static void		vs_map(t_cw *cw)
{
	int32_t		pc;

	pc = -1;
	wattron(cw->vs.map, COLOR_PAIR(cw->map[0].v.col));
	while (++pc < MEM_SIZE)
		if (cw->map[pc].v.bold)
			if (!(--cw->map[pc].v.bold))
			{
				if (cw->map[pc].v.live)
					cw->map[pc].v.live = 0;
				vs_backlight_off_map(cw, pc);
			}
}

static void		select_key(t_cw *cw, int key)
{
	if (key == 'q' && cw->vs.delay <= 15)
		cw->vs.delay += 5;
	else if (key == 'w' && cw->vs.delay < 150)
		cw->vs.delay++;
	else if (key == 'r' && cw->vs.delay >= 5)
		cw->vs.delay -= 5;
	else if (key == 'e' && cw->vs.delay >= 1)
		cw->vs.delay--;
	mvwprintw(cw->vs.header, 3, 23, "%-4u", 150 - (cw->vs.delay * 10));
	wrefresh(cw->vs.header);
	wtimeout(cw->vs.menu, cw->vs.delay);
}

static void		wait_key(t_cw *cw)
{
	int			key;
	uint8_t		prnt;

	prnt = 1;
	while (1)
		if ((key = wgetch(cw->vs.menu)) == 27)
			vs_exit(cw);
		else if (key == 32 || (key == 's' && !cw->f.lg.pause))
			cw->f.lg.pause =\
				(key == 's' || (key == 32 && !cw->f.lg.pause)) ? 1 : 0;
		else if (key == 'q' || key == 'w' || key == 'e' || key == 'r')
			select_key(cw, key);
		else if (!cw->f.lg.pause || key == 's')
		{
			mvwprintw(cw->vs.header, 1, 1, "%s", "** RUNNIG **");
			break ;
		}
		else if (cw->f.lg.pause && prnt--)
		{
			mvwprintw(cw->vs.header, 1, 1, "%s", "** PAUSED **");
			wrefresh(cw->vs.header);
		}
}

void			vs(t_cw *cw, uint8_t mode)
{
	vs_map(cw);
	wnoutrefresh(cw->vs.map);
	mvwprintw(cw->vs.header, 6, 9, "%-7u", cw->cycles);
	if (mode)
	{
		wait_key(cw);
		if (cw->f.lg.vs_live)
			vs_print_lives(cw, 0);
	}
	else
	{
		uint8_t		raw;

		raw = 11 + 4 * cw->num_of_champs;
		mvwprintw(cw->vs.header, 6, 9, "%-7u", cw->cycles);
		mvwprintw(cw->vs.header, 8, 13, "%-7u", cw->num_of_cars);
		mvwprintw(cw->vs.header, 40, 1, "The winner is : ");
		mvwprintw(cw->vs.header, 42, 1, "Press any key to exit");
		wattroff(cw->vs.header, A_BOLD);
		mvwprintw(cw->vs.header, raw, 1, "%s",\
			"[--------------------------------------------------]");
		mvwprintw(cw->vs.header, raw += 3, 1, "%s",\
			"[--------------------------------------------------]");	
		wattron(cw->vs.header, COLOR_PAIR(cw->champ[0]->id) | A_BOLD);
		mvwprintw(cw->vs.header, 40, 17, "%s", cw->champ[0]->head.prog_name);
	}
	wnoutrefresh(cw->vs.header);
	doupdate();
	if (!mode)
	{
		while (wgetch(cw->vs.menu) == ERR)
			sleep(1);
		vs_exit(cw);
	}
}
