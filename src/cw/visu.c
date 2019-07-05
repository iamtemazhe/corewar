/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/05 16:02:21 by jwinthei         ###   ########.fr       */
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
	getmaxyx(stdscr, cw->visu.row, cw->visu.col);
	cw->visu.bkg = newwin(cw->visu.row, cw->visu.col, 0, 0);
	cw->visu.map = newwin(cw->visu.row * 0.9 - 1, cw->visu.col * 3 / 4 - 1, 1, 1);
	cw->visu.header = newwin(cw->visu.row * 0.9 - 1, cw->visu.col / 4 - 1, 1, cw->visu.col * 3 / 4 + 1);
	cw->visu.menu = newwin(cw->visu.row * 0.1 - 1, cw->visu.col - 2, cw->visu.row * 0.9 + 1, 1);	
	wbkgd(cw->visu.bkg, COLOR_PAIR(7));
	wrefresh(cw->visu.bkg);
	wattron(cw->visu.header, COLOR_PAIR(6) | A_BOLD);
	mvwprintw(cw->visu.menu, 1, 1, "%s", "hello world!");
	mvwprintw(cw->visu.menu, 2, 1, "%d",  cw->num_of_champs);
	wrefresh(cw->visu.menu);
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
			wattron(cw->visu.map, COLOR_PAIR(3));
			if (j < cw->champ[i].head.prog_size + (MEM_SIZE / cw->num_of_champs) * i)
				wattron(cw->visu.map, COLOR_PAIR(i + 1));
			mvwprintw(cw->visu.map, k, m++, "%x",cw->map[j++]);
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
	k = 1;
	while (i < cw->num_of_champs)
	{	
		wattron(cw->visu.header, COLOR_PAIR(6) | A_BOLD);
		j = 0;
		m = 1;
		while (cw->champ[i].head.prog_name[j])
		{
			wattron(cw->visu.header, COLOR_PAIR(i + 1) | A_BOLD | A_BLINK);
			mvwprintw(cw->visu.header, k, m++, "%c",  cw->champ[i].head.prog_name[j++]);
			if (m >= cw->visu.col / 4 - 2 && k++)
				m = 1;
		}
		k++;
		i++;
	}
}

void			visu(t_cw *cw)
{
	// init_visu(cw);
	print_map(cw);
	wrefresh(cw->visu.map);
	print_header(cw);
	wrefresh(cw->visu.header);
	sleep(1);
	endwin();
}
