/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:31:08 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/23 18:32:51 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "libft.h"
#include <ncurses.h>

void			print_map(t_cw *cw)
{
	uint		k;
	uint		m;
	uint		j;

	j = 0;
	k = 1;
	m = 1;
	while (j < MEM_SIZE)
	{	
		wattron(cw->visu.map, COLOR_PAIR(cw->map[j].v.c_co));	
		mvwprintw(cw->visu.map, k, m++, "%.2x", cw->map[j++].v.code);
		m += 2;
		if (m > MAP_X && k++)
			m = 1;
	}
	wnoutrefresh(cw->visu.map);
}

void			print_header_1(t_cw *cw)
{
	uint		k;

	k = 10 + 4 * cw->num_of_champs;
	wattron(cw->visu.header, COLOR_PAIR(15) | A_BOLD);
	mvwprintw(cw->visu.header, k, 1, "%s",\
			"Live breakdown for current period :");
	mvwprintw(cw->visu.header, k += 3, 1, "%s",\
			"Live breakdown for last period :");
	wattron(cw->visu.header, COLOR_PAIR(14) | A_BOLD);
	mvwprintw(cw->visu.header, k -= 2, 1, "%s",\
			"[------------------------------------------------]");
	mvwprintw(cw->visu.header, k += 3, 1, "%s",\
			"[------------------------------------------------]");
	wattron(cw->visu.header, COLOR_PAIR(15) | A_BOLD);
	mvwprintw(cw->visu.header, k += 2, 1, "%s : %-10d", "CYCLE_TO_DIE",\
														cw->cycle_to_die);
	mvwprintw(cw->visu.header, k += 2, 1, "%s : %d", "CYCLE_DELTA",\
															CYCLE_DELTA);
	mvwprintw(cw->visu.header, k += 2, 1, "%s : %d", "NBR_LIVE", NBR_LIVE);
	mvwprintw(cw->visu.header, k += 2, 1, "%s : %d", "MAX_CHECKS", MAX_CHECKS);
}

void			print_header(t_cw *cw)
{
	uint		k;
	uint		i;

	i = 0;
	k = 9;
	wattron(cw->visu.header, COLOR_PAIR(15) | A_BOLD);
	mvwprintw(cw->visu.header, 1, 1, "%s", "** PAUSED **");
	mvwprintw(cw->visu.header, 3, 1, "%s %5d", "Cycles/second limit :",\
											1000 - (cw->visu.delay * 10));
	mvwprintw(cw->visu.header, 6, 1, "%s %-6d", "Cycle :", cw->cycles);
	mvwprintw(cw->visu.header, 8, 1, "%s %d", "Processes :", cw->num_of_cars);
	while (i < cw->num_of_champs)
	{
		mvwprintw(cw->visu.header, ++k, 1, "%s%d : ", "Player -", i + 1);
		wattron(cw->visu.header, COLOR_PAIR(cw->champ[i]->id * 2 - 1) | A_BOLD);
		mvwprintw(cw->visu.header, k++, 14, "%.52s",\
											cw->champ[i]->head.prog_name);
		wattron(cw->visu.header, COLOR_PAIR(15) | A_BOLD);
		mvwprintw(cw->visu.header, k++, 5, "%-27s %d", "Last live :",\
											cw->champ[i]->last_live);
		mvwprintw(cw->visu.header, k++, 5, "%-27s %d",\
					"Lives in current period :", cw->champ[i++]->lives);
	}
	print_header_1(cw);
	wnoutrefresh(cw->visu.header);
}

void			print_menu(t_cw *cw)
{
	wattron(cw->visu.menu, COLOR_PAIR(15) | A_BOLD);
	mvwprintw(cw->visu.menu, 1, 129, "%s", "MENU");
	mvwprintw(cw->visu.menu, 2, 1, "%s", "Esc for exit");
	mvwprintw(cw->visu.menu, 2, 20, "%s", "Spase for pause | run");
	mvwprintw(cw->visu.menu, 2, 50, "%s", "For step by step s");
	mvwprintw(cw->visu.menu, 2, 80, "%s", "Speed q | w | e | r");
		
	keypad(cw->visu.menu, TRUE);
	noecho();
	timeout(1);
	cbreak();
	wnoutrefresh(cw->visu.menu);
}

void			print_maps(t_cw *cw)
{
	wbkgd(cw->visu.bkg, COLOR_PAIR(16));
	wrefresh(cw->visu.bkg);
	print_map(cw);
	wrefresh(cw->visu.map);
	print_header(cw);
	print_menu(cw);
	doupdate();
	nodelay(cw->visu.menu, true);
	cbreak();
	noecho();
	wtimeout(cw->visu.menu, cw->visu.delay);
	doupdate();
}

void			init_visu(t_cw *cw)
{
	initscr();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_BLUE);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_YELLOW);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(9, COLOR_WHITE, COLOR_GREEN);
	init_pair(10, COLOR_WHITE, COLOR_BLUE);
	init_pair(11, COLOR_WHITE, COLOR_YELLOW);	
	init_pair(13, COLOR_WHITE, COLOR_MAGENTA);	
	init_pair(14, COLOR_GRAY, COLOR_BLACK);
	init_pair(15, COLOR_WHITE, COLOR_BLACK);
	init_pair(16, COLOR_BLACK, COLOR_GRAY);
	init_pair(17, COLOR_BLACK, COLOR_RED);
	cw->visu.bkg = newwin(80, 264, 0, 0);
	cw->visu.map = newwin(67, 194, 1, 1);
	cw->visu.header = newwin(67, 67, 1, 196);
	cw->visu.menu = newwin(10, 262, 69, 1);
	cw->f.lg.pause = 1;
	cw->visu.delay = 95;
	print_maps(cw);
}
