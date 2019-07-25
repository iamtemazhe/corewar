#include "cw.h"
#include "libft.h"
#include <ncurses.h>

static void		print_map(t_cw *cw)
{
	uint8_t		k;
	uint8_t		m;
	uint32_t	j;

	j = 0;
	k = 1;
	m = 1;
	while (j < MEM_SIZE)
	{	
		wattron(cw->vs.map, COLOR_PAIR(cw->map[j].v.col));	
		mvwprintw(cw->vs.map, k, m++, "%.2x", cw->map[j++].v.code);
		m += 2;
		if (m > MAP_X && k++)
			m = 1;
	}
}

static void		print_header_1(t_cw *cw)
{
	uint8_t		k;

	k = 10 + 4 * cw->num_of_champs;
	mvwprintw(cw->vs.header, k, 1, "%s",\
			"Live breakdown for current period :");
	mvwprintw(cw->vs.header, k += 3, 1, "%s",\
			"Live breakdown for last period :");
	wattroff(cw->vs.header, A_BOLD);
	mvwprintw(cw->vs.header, k -= 2, 1, "%s",\
			"[--------------------------------------------------]");
	mvwprintw(cw->vs.header, k += 3, 1, "%s",\
			"[--------------------------------------------------]");
	wattron(cw->vs.header, COLOR_PAIR(COL_TEXT) | A_BOLD);
	mvwprintw(cw->vs.header, k += 2, 1, "%s : %-10u", "CYCLE_TO_DIE",\
														cw->cycle_to_die);
	mvwprintw(cw->vs.header, k += 2, 1, "%s : %u", "CYCLE_DELTA",\
															CYCLE_DELTA);
	mvwprintw(cw->vs.header, k += 2, 1, "%s : %u", "NBR_LIVE", NBR_LIVE);
	mvwprintw(cw->vs.header, k += 2, 1, "%s : %u", "MAX_CHECKS", MAX_CHECKS);
}

static void		print_header(t_cw *cw)
{
	uint8_t		k;
	uint8_t		i;

	i = 0;
	k = 9;
	mvwprintw(cw->vs.header, 1, 1, "%s", "** PAUSED **");
	mvwprintw(cw->vs.header, 3, 1, "%s %-4u", "Cycles/second limit :",\
											1000 - (cw->vs.delay * 10));
	mvwprintw(cw->vs.header, 6, 1, "%s %-7u", "Cycle :", cw->cycles);
	mvwprintw(cw->vs.header, 8, 1, "%s %-7u", "Processes :", cw->num_of_cars);
	while (i < cw->num_of_champs)
	{
		mvwprintw(cw->vs.header, ++k, 1, "%s%u : ", "Player -", cw->champ[i]->id);
		wattron(cw->vs.header, COLOR_PAIR(cw->champ[i]->id) | A_BOLD);
		mvwprintw(cw->vs.header, k++, 14, "%.52s",\
											cw->champ[i]->head.prog_name);
		wattron(cw->vs.header, COLOR_PAIR(COL_TEXT) | A_BOLD);
		mvwprintw(cw->vs.header, k++, 5, "%s %21u", "Last live :",\
											cw->champ[i]->last_live);
		mvwprintw(cw->vs.header, k++, 5, "%s %7u",\
					"Lives in current period :", cw->champ[i++]->lives);
	}
	print_header_1(cw);
}

static void		print_menu(t_cw *cw)
{
	mvwprintw(cw->vs.menu, 1, 129, "%s", "MENU");
	mvwprintw(cw->vs.menu, 2, 1, "%s", "Esc for exit");
	mvwprintw(cw->vs.menu, 2, 20, "%s", "Spase for pause | run");
	mvwprintw(cw->vs.menu, 2, 50, "%s", "For step by step s");
	mvwprintw(cw->vs.menu, 2, 80, "%s", "Speed q | w | e | r");		
	keypad(cw->vs.menu, TRUE);
}

void			vs_print_windows(t_cw *cw)
{
	cw->vs.bkg = newwin(80, 264, 0, 0);
	cw->vs.map = newwin(67, 194, 1, 1);
	cw->vs.header = newwin(67, 67, 1, 196);
	cw->vs.menu = newwin(10, 262, 69, 1);
	cw->f.lg.pause = 1;
	cw->vs.delay = 95;
	wbkgd(cw->vs.bkg, COLOR_PAIR(COL_BACK));
	wattron(cw->vs.menu, COLOR_PAIR(COL_TEXT) | A_BOLD);
	wattron(cw->vs.header, COLOR_PAIR(COL_TEXT) | A_BOLD);
	wrefresh(cw->vs.bkg);
	print_map(cw);
	print_header(cw);
	print_menu(cw);
	nodelay(cw->vs.menu, true);
	cbreak();
	noecho();
	wtimeout(cw->vs.menu, cw->vs.delay);
	wnoutrefresh(cw->vs.menu);
}