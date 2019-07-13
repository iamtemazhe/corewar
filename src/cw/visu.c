/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/13 19:26:17 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "libft.h"
#include <ncurses.h>
#include <panel.h>

#define COLOR_GRAY 8

void			init_visu(t_cw *cw)
{
	initscr();
	curs_set(0);
	start_color();
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_GRAY, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_GRAY);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	getmaxyx(stdscr, cw->visu.row, cw->visu.col);
	cw->visu.bkg = newwin(cw->visu.row, cw->visu.col, 0, 0);
	cw->visu.map = newwin(cw->visu.row * 0.9 - 1, cw->visu.col * 3 / 4 - 1, 1, 1);
	cw->visu.header = newwin(cw->visu.row * 0.9 - 1, cw->visu.col / 4 - 1, 1, cw->visu.col * 3 / 4 + 1);
	cw->visu.menu = newwin(cw->visu.row * 0.1 - 1, cw->visu.col - 2, cw->visu.row * 0.9 + 1, 1);	
	wbkgd(cw->visu.bkg, COLOR_PAIR(7));
	wrefresh(cw->visu.bkg);
	wattron(cw->visu.header, COLOR_PAIR(6) | A_BOLD);
	//mvwprintw(cw->visu.menu, 1, 1, "%s", "hello world!");
	//mvwprintw(cw->visu.menu, 2, 1, "%d",  cw->num_of_champs);
	//wrefresh(cw->visu.menu);
	//keypad(cw->visu.menu, TRUE);
}

void			print_map(t_cw *cw)
{
	uint		k;
	uint		m;
	uint		i;
	uint		j;

	i = 0;
	j = 0;
	k = 1;
	m = 1;
	while (i < cw->num_of_champs && j < MEM_SIZE)
	{
		while (j < (MEM_SIZE / cw->num_of_champs) * (i + 1) && j < MEM_SIZE)
		{
			wattron(cw->visu.map, COLOR_PAIR(3) | A_BOLD);
			if (j < cw->champ[i].head.prog_size + (MEM_SIZE / cw->num_of_champs) * i)
				wattron(cw->visu.map, COLOR_PAIR(i + 1));
			mvwprintw(cw->visu.map, k, m++, "%.2x",cw->map[j++]);
			m += 2;
			if (m >= cw->visu.col / 4 * 3 - 2 && k++)
				m = 1;
		}
		i++;
	}
}

void			print_header(t_cw *cw)
{
	uint		k;
	uint		m;
	uint		i;
	uint		j;

	i = 0;
	wattron(cw->visu.header, COLOR_PAIR(6) | A_BOLD);
	mvwprintw(cw->visu.header, 1, 1,"%s", "** STATUS **");
	mvwprintw(cw->visu.header, 3, 1,"%s %d", "Cycles/second limit :", 0);
	mvwprintw(cw->visu.header, 6, 1,"%s %d", "Cycle :", 0);
	mvwprintw(cw->visu.header, 8, 1,"%s %d", "Processes :", cw->num_of_cars);
	k = 10;
	while (i < cw->num_of_champs)
	{	
		wattron(cw->visu.header, COLOR_PAIR(6) | A_BOLD);
		j = 0;
		m = 13;
		wattron(cw->visu.header, COLOR_PAIR(6) | A_BOLD);
		mvwprintw(cw->visu.header, k, 1, "%s%d : ",  "Player -", i + 1);
		while (cw->champ[i].head.prog_name[j])
		{
			wattron(cw->visu.header, COLOR_PAIR(i + 1) | A_BOLD);
			mvwprintw(cw->visu.header, k, m++, "%c", cw->champ[i].head.prog_name[j++]);
			if (m >= cw->visu.col / 4 - 2 && k++)
				m = 1;
		}
		wattron(cw->visu.header, COLOR_PAIR(6) | A_BOLD);
		mvwprintw(cw->visu.header, ++k, 5,"%-25s %d", "Last live :", 0);
		mvwprintw(cw->visu.header, ++k, 5,"%-25s %d", "Lives in current period :", 0);
		k += 2;
		i++;
	}
	i = 0;
	while (i < cw->num_of_champs)
	{
		wattron(cw->visu.header, COLOR_PAIR(6) | A_BOLD);
		mvwprintw(cw->visu.header, k++, 1,"%s", "Live breakdown for current period :");
		wattron(cw->visu.header, COLOR_PAIR(3) | A_BOLD);
		mvwprintw(cw->visu.header, k++, 1,"%s", "[------------------------------------------------]");
		k++;
		i++;
	}
	wattron(cw->visu.header, COLOR_PAIR(6) | A_BOLD);
	mvwprintw(cw->visu.header, k, 1,"%s : %d", "CYCLE_TO_DIE", cw->cycle_to_die);
	mvwprintw(cw->visu.header, k += 2, 1,"%s : %d", "CYCLE_DELTA", CYCLE_DELTA);
	mvwprintw(cw->visu.header, k += 2, 1,"%s : %d", "NBR_LIVE", NBR_LIVE);
	mvwprintw(cw->visu.header, k += 2, 1,"%s : %d", "MAX_CHECKS", MAX_CHECKS);
}

void			print_menu(t_cw *cw)
{
	wattron(cw->visu.menu, COLOR_PAIR(6) | A_BOLD);
	mvwprintw(cw->visu.menu, 1, cw->visu.col / 2 - 2, "%-20s",  "MENU");
	mvwprintw(cw->visu.menu, 2, 1, "%-20s",  "Esc for exit");
	wrefresh(cw->visu.menu);
	keypad(cw->visu.menu, TRUE);
}

void			visu_exit(t_cw *cw)
{
	delwin(cw->visu.menu);
	delwin(cw->visu.map);
	delwin(cw->visu.header);
	endwin();
//	free(cw);
	exit(0);
}

void			select_key(t_cw *cw)
{
	noecho();
	halfdelay(5);
	if (wgetch(cw->visu.menu) == ERR)
		sleep(1);
	else if (wgetch(cw->visu.menu) == 27)
		visu_exit(cw);
}

void			visu(t_cw *cw)
{
	int			i = 0;

	scrollok(cw->visu.map, true);
	wrefresh(cw->visu.map);
	while (i < 3)
	{	
		print_map(cw);
		wrefresh(cw->visu.map);
		print_header(cw);
		wrefresh(cw->visu.header);
		mvwprintw(cw->visu.menu, 3, 1, "%d", i);
		print_menu(cw);
		select_key(cw);
		if (i == 2)
		{
			wattron(cw->visu.map, COLOR_PAIR(1) | A_BOLD);			
			mvwprintw(cw->visu.map, 1, 1, "%.2x", 0);
			mvwprintw(cw->visu.map, 8, 1, "%.2x",cw->map[364]);
			wrefresh(cw->visu.map);
		}
		i++;
	}
}
