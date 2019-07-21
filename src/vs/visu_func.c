/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:45:08 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/21 17:14:47 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "libft.h"
#include <ncurses.h>

void			visu_exit(t_cw *cw)
{
	delwin(cw->visu.menu);
	delwin(cw->visu.map);
	delwin(cw->visu.header);
	endwin();
//	free(cw);
	exit(0);
}

void				print_cycle_to_die(t_cw *cw)
{
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, 16 + 4 * cw->num_of_champs, 16, "%-10d", cw->cycle_to_die);
	wnoutrefresh(cw->visu.header);	
}

void				print_cycles(t_cw *cw)
{
	int				i;
	int				k;

	i = 0;
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwprintw(cw->visu.header, 6, 9, "%-6d", cw->cycles);
	mvwprintw(cw->visu.header, 8, 13,"%-6d", cw->num_of_cars);
	k = 11;
	while (i < cw->num_of_champs)
	{
		mvwprintw(cw->visu.header, k, 31,"%5d", cw->champ[i]->last_live);
		mvwprintw(cw->visu.header, ++k, 31,"%5d", cw->champ[i++]->lives);
		k += 3;
	}
	wnoutrefresh(cw->visu.header);
}

void			select_key(t_cw *cw, int key)
{
	if (key == 'q')
		visu_exit(cw);
	else if (key == 32)
	{
		mvwprintw(cw->visu.header, 1, 1, "%s", "** PAUSED **");
		wnoutrefresh(cw->visu.header);
		doupdate();
		while ((key = wgetch(cw->visu.menu)) != 32)		
			if (key == 'q')
				visu_exit(cw);
		mvwprintw(cw->visu.header, 1, 1, "%s", "** RUNNIG **");
	}
	else if (key == 'w' || key == 'e')
	{
		wtimeout(cw->visu.menu, cw->visu.delay += (key == 'e') ? 10 : 1);
		mvwprintw(cw->visu.header, 3, 1, "%s %5d", "Cycles/second limit :", cw->visu.delay);
	}
	else if (key == 's' || key == 'd')
	{
		wtimeout(cw->visu.menu, cw->visu.delay -= (key == 'd') ? 10 : 1);
		mvwprintw(cw->visu.header, 3, 1, "%s %5d", "Cycles/second limit :", cw->visu.delay);
	}
	wrefresh(cw->visu.header);
	wnoutrefresh(cw->visu.header);
}
