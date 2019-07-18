/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/18 20:43:46 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "libft.h"
#include <ncurses.h>

#define COLOR_GRAY 8

void			print_map(t_cw *cw)
{
	uint		k;
	uint		m;
	uint		i;
	uint		j;
	uint		x;
	uint		y;

	i = 0;
	j = 0;
	k = 1;
	m = 1;
	getmaxyx(cw->visu.map, y, x);
	while (i < cw->num_of_champs && j < MEM_SIZE)
	{
		while (j < (MEM_SIZE / cw->num_of_champs) * (i + 1) && j < MEM_SIZE)
		{
			wattron(cw->visu.map, COLOR_PAIR(9) | A_BOLD);
			if (j < cw->champ[i].head.prog_size + (MEM_SIZE / cw->num_of_champs) * i)
				wattron(cw->visu.map, COLOR_PAIR(i * 2 + 1));
			mvwprintw(cw->visu.map, k, m++, "%.2x",cw->map[j++]);
			m += 2;
			if (m > x - 2 && k++)
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
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, 6, 1,"%s %d", "Cycle :", cw->cycles);
	mvwprintw(cw->visu.header, 8, 1,"%s %d", "Processes :", cw->num_of_cars);
	k = 10;
	while (i < cw->num_of_champs)
	{	
		wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
		j = 0;
		m = 13;
		wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
		mvwprintw(cw->visu.header, k, 1, "%s%d : ",  "Player -", i + 1);
		while (cw->champ[i].head.prog_name[j])
		{
			wattron(cw->visu.header, COLOR_PAIR(i * 2 + 1) | A_BOLD);
			mvwprintw(cw->visu.header, k, m++, "%c", cw->champ[i].head.prog_name[j++]);
			if (m >= cw->visu.col / 4 - 2 && k++)
				m = 1;
		}
		wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
		mvwprintw(cw->visu.header, ++k, 5,"%-25s %d", "Last live :", cw->champ[i].last_live);
		mvwprintw(cw->visu.header, ++k, 5,"%-25s %d", "Lives in current period :", cw->champ[i].lives);
		k += 2;
		i++;
	}
	
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, k++, 1,"%s", "Live breakdown for current period :");
	wattron(cw->visu.header, COLOR_PAIR(9) | A_BOLD);
	mvwprintw(cw->visu.header, k++, 1,"%s", "[------------------------------------------------]");
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);	
	mvwprintw(cw->visu.header, k++, 1,"%s", "Live breakdown for last period :");
	wattron(cw->visu.header, COLOR_PAIR(9) | A_BOLD);
	mvwprintw(cw->visu.header, k++, 1,"%s", "[------------------------------------------------]");
	
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, ++k, 1,"%s : %d", "CYCLE_TO_DIE", cw->cycle_to_die);
	mvwprintw(cw->visu.header, k += 2, 1,"%s : %d", "CYCLE_DELTA", CYCLE_DELTA);
	mvwprintw(cw->visu.header, k += 2, 1,"%s : %d", "NBR_LIVE", NBR_LIVE);
	mvwprintw(cw->visu.header, k += 2, 1,"%s : %d", "MAX_CHECKS", MAX_CHECKS);
}

void			print_menu(t_cw *cw)
{
	wattron(cw->visu.menu, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.menu, 1, cw->visu.col / 2 - 2, "%-20s",  "MENU");
	mvwprintw(cw->visu.menu, 2, 1, "%s",  "Q for exit");
	mvwprintw(cw->visu.menu, 2, 20, "%s",  "Spase for pause / run");
	mvwprintw(cw->visu.menu, 2, 50, "%s",  "Speed w / s");
	wrefresh(cw->visu.menu);
	keypad(cw->visu.menu, TRUE);
	noecho();
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

void			select_key(t_cw *cw, int key, int *w)
{
	if (key == 'q')
		visu_exit(cw);
	else if (key == 32)
	{
		mvwprintw(cw->visu.header, 1, 1,"%s", "** PAUSED **");
		wrefresh(cw->visu.header);
		while ((key = wgetch(cw->visu.menu)) != 32)
			if (key == 'q')
				visu_exit(cw);
		halfdelay(*w);	
		mvwprintw(cw->visu.header, 1, 1,"%s", "** RUNNIG **");
		wrefresh(cw->visu.header);	
	}
	else if (key == 'w')
	{
		halfdelay(++*w);
		mvwprintw(cw->visu.header, 3, 1,"%s %5d", "Cycles/second limit :", *w);
		wrefresh(cw->visu.header);
	}
	else if (key == 's')
	{
		halfdelay(--*w);	
		mvwprintw(cw->visu.header, 3, 1,"%s %5d", "Cycles/second limit :", *w);
		wrefresh(cw->visu.header);	
	}	
}

void			vs_logi(t_cw *cw, uint8_t i_car, int *d)
{
	uint8_t		col;
	int			x;
	int			y;
	int			j;

	//col = -cw->car[IN(cw->car[i_car]->op_code)]->reg[0];
	col = 1;
	j = 0;
	getmaxyx(cw->visu.map, y, x);
	//mvwprintw(cw->visu.menu, 4, 25, "% col", col);
	wattron(cw->visu.map, COLOR_PAIR(col * 2) | A_BOLD);
	//mvwprintw(cw->visu.map, cw->car[i_car]->pc * 3 / x + 1, cw->car[i_car]->pc * 3 % x + 1, "%.2x", cw->map[cw->car[i_car]->pc]);
	mvwprintw(cw->visu.map, i_car * 3 / (x - 2) + 1, i_car * 3 % (x - 2) + 1, "%.2x", cw->map[i_car]);
	wrefresh(cw->visu.map);
	//sleep(1);
	mvwprintw(cw->visu.map, i_car * 3 / (x - 2) + 1, i_car * 3 % (x - 2) + 1, "%.2x", cw->map[i_car]);	
	select_key(cw, wgetch(cw->visu.menu), d);
	while (j < 4)
	{
		wattron(cw->visu.map, COLOR_PAIR(col * 2 + 1) | A_BOLD);	
		mvwprintw(cw->visu.map, i_car * 3 / (x - 2) + 1, i_car * 3 % (x - 2) + 1, "%.2x", cw->map[i_car]);	
		i_car++;	
		j++;
	}
	wrefresh(cw->visu.map);
}

void			vs_backlight_car(t_cw *cw, size_t i_car, uint8_t mod)
{
	uint8_t		col;
	int			x;
	int			y;

	col = -cw->car[i_car]->reg[0];
	getmaxyx(cw->visu.map, y, x);
	wattron(cw->visu.map, ((mod) ? COLOR_PAIR(col * 2) : COLOR_PAIR(col * 2 - 1)) | A_BOLD);
	mvwprintw(cw->visu.map, cw->car[i_car]->pc * 3 / (x - 1) + 1, cw->car[i_car]->pc * 3 % (x - 1) + 1, "%.2x", cw->map[cw->car[i_car]->pc]);
	wrefresh(cw->visu.map);
}

void			vs_backlight_map(t_cw *cw, t_stack *st_op, uint8_t mod)
{
	int			x;
	int			y;
	uint8_t		j;

	j = 0;
	getmaxyx(cw->visu.map, y, x);
	wattron(cw->visu.map, COLOR_PAIR(st_op->id * 2 + 1) | (mod) ? A_BOLD : 0);
	while (++j < st_op->size)
	{
		mvwprintw(cw->visu.map, st_op->pc * 3 / (x - 1) + 1, st_op->pc * 3 % (x - 1) + 1, "%.2x", st_op->pc);
		st_op->pc = PCV(st_op->pc + j);
	}
	wrefresh(cw->visu.map);
}

void			visu(t_cw *cw)
{
	int			delay;

	delay = 1;
	select_key(cw, wgetch(cw->visu.menu), &delay);
	print_header(cw);
	wrefresh(cw->visu.header);
	if (!cw->visu.st_op)
		return ;
	while ((cw->visu.st_op = cw->visu.st_op->prev))
	{
		if (cw->cycles - cw->visu.st_op->cycle_to_show >= CYCLE_TO_SHOW)
		{
			vs_backlight_map(cw, cw->visu.st_op, 0);
			st_del(&cw->visu.st_op);
		}
		else
			break ;
	}
		
}

void			print_windows(t_cw *cw)
{
	wbkgd(cw->visu.bkg, COLOR_PAIR(11));
	wrefresh(cw->visu.bkg);
	print_map(cw);
	wrefresh(cw->visu.map);
	print_header(cw);
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, 1, 1,"%s", "** PAUSED **");
	mvwprintw(cw->visu.header, 3, 1,"%s %d", "Cycles/second limit :", 0);
	wrefresh(cw->visu.header);
	print_menu(cw);
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
	init_pair(9, COLOR_GRAY, COLOR_BLACK);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_GRAY);
	init_pair(12, COLOR_BLACK, COLOR_RED);
	getmaxyx(stdscr, cw->visu.row, cw->visu.col);
	cw->visu.bkg = newwin(cw->visu.row, cw->visu.col, 0, 0);
	cw->visu.map = newwin(cw->visu.row * 0.9 - 1, cw->visu.col * 3 / 4 - 1, 1, 1);
	cw->visu.header = newwin(cw->visu.row * 0.9 - 1, cw->visu.col / 4 - 1, 1, cw->visu.col * 3 / 4 + 1);
	cw->visu.menu = newwin(cw->visu.row * 0.1 - 1, cw->visu.col - 2, cw->visu.row * 0.9 + 1, 1);
	print_windows(cw);	
}
