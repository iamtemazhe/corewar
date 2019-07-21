/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/21 12:04:43 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "libft.h"
#include <ncurses.h>

#define COLOR_GRAY 8
#define MAP_X 194

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
			wattron(cw->visu.map, COLOR_PAIR(9));
			if (j < cw->champ[i]->head.prog_size + (MEM_SIZE / cw->num_of_champs) * i)
				wattron(cw->visu.map, COLOR_PAIR(i * 2 + 1));
			mvwprintw(cw->visu.map, k, m++, "%.2x", cw->map[j++]);
			m += 2;
			if (m > MAP_X - 2 && k++)	
				m = 1;
		}
		i++;
	}
	wnoutrefresh(cw->visu.map);
}

void			print_header_1(t_cw *cw)
{
	uint		k;

	k = 10 + 4 * cw->num_of_champs;
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, k, 1,"%s", "Live breakdown for current period :");
	mvwprintw(cw->visu.header, k += 3, 1,"%s", "Live breakdown for last period :");
	wattron(cw->visu.header, COLOR_PAIR(9) | A_BOLD);
	mvwprintw(cw->visu.header, k -= 2, 1,"%s", "[------------------------------------------------]");
	mvwprintw(cw->visu.header, k += 3, 1,"%s", "[------------------------------------------------]");
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, k += 2, 1,"%s : %-10d", "CYCLE_TO_DIE", cw->cycle_to_die);
	mvwprintw(cw->visu.header, k += 2, 1,"%s : %d", "CYCLE_DELTA", CYCLE_DELTA);
	mvwprintw(cw->visu.header, k += 2, 1,"%s : %d", "NBR_LIVE", NBR_LIVE);
	mvwprintw(cw->visu.header, k += 2, 1,"%s : %d", "MAX_CHECKS", MAX_CHECKS);
	//wnoutrefresh(cw->visu.header);
}

void			print_header(t_cw *cw)
{
	uint		k;
	uint		i;

	i = 0;
	k = 9;
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, 1, 1,"%s", "** PAUSED **");
	mvwprintw(cw->visu.header, 3, 1,"%s %5d", "Cycles/second limit :", 0);
	mvwprintw(cw->visu.header, 6, 1,"%s %-6d", "Cycle :", cw->cycles);
	mvwprintw(cw->visu.header, 8, 1,"%s %d", "Processes :", cw->num_of_cars);
	while (i < cw->num_of_champs)
	{	
		mvwprintw(cw->visu.header, ++k, 1, "%s%d : ",  "Player -", i + 1);
		wattron(cw->visu.header, COLOR_PAIR(i * 2 + 1) | A_BOLD);
		mvwprintw(cw->visu.header, k++, 13, "%.52s", cw->champ[i]->head.prog_name);	
		wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
		mvwprintw(cw->visu.header, k++, 5,"%-25s %d", "Last live :", cw->champ[i]->last_live);
		mvwprintw(cw->visu.header, k++, 5,"%-25s %d", "Lives in current period :", cw->champ[i++]->lives);
	}
	print_header_1(cw);
	wnoutrefresh(cw->visu.header);
}

void			print_menu(t_cw *cw)
{
	wattron(cw->visu.menu, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.menu, 1, 129, "%s",  "MENU");
	mvwprintw(cw->visu.menu, 2, 1, "%s",  "Q for exit");
	mvwprintw(cw->visu.menu, 2, 20, "%s",  "Spase for pause / run");
	mvwprintw(cw->visu.menu, 2, 50, "%s",  "Speed w / s");
	keypad(cw->visu.menu, TRUE);
	noecho();
	timeout(1);
	//nonl();
	cbreak();
	
	wnoutrefresh(cw->visu.menu);
	//wrefresh(cw->visu.menu);
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
		nodelay(cw->visu.menu, true);
		cbreak();
		noecho();
		wtimeout(cw->visu.menu, *w);
		mvwprintw(cw->visu.header, 1, 1, "%s", "** PAUSED **");
		wnoutrefresh(cw->visu.header);
		doupdate();
		while ((key = wgetch(cw->visu.menu)) != 32)		
			if (key == 'q')
				visu_exit(cw);
		mvwprintw(cw->visu.header, 1, 1, "%s", "** RUNNIG **");
		mvwprintw(cw->visu.header, 3, 1, "%s %5d", "Cycles/second limit :", *w);
	}
	else if (key == 'w')
	{
		timeout(++*w);
		mvwprintw(cw->visu.header, 3, 1, "%s %5d", "Cycles/second limit :", *w);
	}
	else if (key == 's')
	{
		timeout(--*w);	
		mvwprintw(cw->visu.header, 3, 1, "%s %5d", "Cycles/second limit :", *w);
	}
	wrefresh(cw->visu.header);
	wnoutrefresh(cw->visu.header);
}

void			vs_backlight_map(t_cw *cw, t_stack *st_op, uint8_t mod)
{
	uint8_t		i;
	int32_t		pc;

	i = 0;
	pc = st_op->pc;
	wattron(cw->visu.map, COLOR_PAIR(st_op->id * 2 - 1) | A_BOLD);
	if (!mod)
		wattroff(cw->visu.map, A_BOLD);
	while (++i <= st_op->size)
	{
		mvwprintw(cw->visu.map, pc * 3 / (MAP_X - 2) + 1, pc * 3 % (MAP_X - 2) + 1, "%.2x", cw->map[PCV(pc)]);
		pc++;
	}
	if (mod)
		wattroff(cw->visu.map, A_BOLD);
	wnoutrefresh(cw->visu.map);
}


void			vs_backlight_car(t_cw *cw, size_t i_car, int32_t step)
{
	uint8_t		col;
	uint32_t	pc_prev;
	uint32_t	pc;

	pc_prev = cw->car[i_car]->pc;
	pc = PCV(pc_prev + step);
	col = -cw->car[i_car]->reg[0];
	wattron(cw->visu.map, COLOR_PAIR(col * 2 - 1));
	mvwprintw(cw->visu.map, pc_prev * 3 / (MAP_X - 2) + 1, pc_prev * 3 % (MAP_X - 2) + 1, "%.2x", cw->map[pc_prev]);
	wattron(cw->visu.map, COLOR_PAIR(col * 2));
	mvwprintw(cw->visu.map, pc * 3 / (MAP_X - 2) + 1, pc * 3 % (MAP_X - 2) + 1, "%.2x", cw->map[pc]);
	mvwprintw(cw->visu.menu, 4, 10, "y = %3u x = %3u map = %02x pos = %4u, id_car = %u", pc_prev * 3 / (MAP_X - 2) + 1, pc_prev * 3 % (MAP_X - 2) + 1, cw->map[pc_prev], pc_prev, i_car + 1);
	mvwprintw(cw->visu.menu, 5, 10, "y = %3u x = %3u map = %02x pos = %4u", pc * 3 / (MAP_X - 2) + 1, pc * 3 % (MAP_X - 2) + 1, cw->map[pc], pc);
	wnoutrefresh(cw->visu.menu);
	wnoutrefresh(cw->visu.map);
	//wrefresh(cw->visu.map);
}

void			vs_backlight_new_car(t_cw *cw, uint8_t col, int32_t pc)
{
	wattron(cw->visu.map, COLOR_PAIR(col * 2));
	mvwprintw(cw->visu.map, pc * 3 / (MAP_X - 2) + 1, pc * 3 % (MAP_X - 2) + 1, "%.2x", cw->map[pc]);
	wnoutrefresh(cw->visu.map);
}


void				print_cycle_to_die(t_cw *cw)
{
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, 16 + 4 * cw->num_of_champs, 16, "%-10d", cw->cycle_to_die);
	wnoutrefresh(cw->visu.header);	
}

void				print_cycles(t_cw *cw)
{
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, 6, 9, "%-6d", cw->cycles);
	mvwprintw(cw->visu.header, 8, 13,"%-6d", cw->num_of_cars);
	wnoutrefresh(cw->visu.header);
}

void			visu(t_cw *cw)
{
	int			delay;
	t_stack		*tmp;

	delay = 5;
	timeout (delay);
	select_key(cw, wgetch(cw->visu.menu), &delay);
	//sleep(1);
	print_cycles(cw);
	doupdate();
	if (cw->visu.st_op)
	{
		tmp = cw->visu.st_op;
		while (tmp)
		{
			tmp = tmp->prev;
			if (tmp->n == cw->visu.st_op->n)
				break;
			if (cw->cycles - tmp->cycle_to_show >= CYCLE_TO_SHOW)
			{
				vs_backlight_map(cw, tmp, 0);
				st_del(&tmp);
			}
			else
				break ;
		}
	}	
}

void			print_windows(t_cw *cw)
{
	wbkgd(cw->visu.bkg, COLOR_PAIR(11));	wrefresh(cw->visu.bkg);
	print_map(cw);
	//wrefresh(cw->visu.map);
	print_header(cw);
	//wrefresh(cw->visu.header);
	print_menu(cw);
	//wrefresh(cw->visu.menu);
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
	init_pair(9, COLOR_GRAY, COLOR_BLACK);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_GRAY);
	init_pair(12, COLOR_BLACK, COLOR_RED);
	cw->visu.bkg = newwin(80, 264, 0, 0);
	cw->visu.map = newwin(67, 194, 1, 1);
	cw->visu.header = newwin(67, 67, 1, 196);
	cw->visu.menu = newwin(10, 262, 69, 1);
	print_windows(cw);
}
