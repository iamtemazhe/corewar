/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:45:08 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/22 22:06:15 by jwinthei         ###   ########.fr       */
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

void			print_lives(t_cw *cw, uint8_t mod)
{
	uint8_t		i;
	uint8_t		raw;
	uint8_t		colum;
	size_t		lives;

	i = 0;
	colum = 1;
	raw = cw->num_of_champs * 4;
	raw += (mod) ? 14 : 11;
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	if (!cw->lives)
	{
		mvwprintw(cw->visu.header, raw, 1, "%s", "[------------------------------------------------]");
		return ;
	}
	mvwprintw(cw->visu.header, raw, 1, "%s", "[");
	while (i < cw->num_of_champs)
	{
		wattron(cw->visu.header, COLOR_PAIR((i + 1) * 2 - 1));
		lives = (cw->champ[i++]->lives / cw->lives) * LIVES_TO_SHOW;
		while (lives-- > 0 && ++colum < 50)
			mvwaddch(cw->visu.header, raw, colum, '-');
	}
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	mvwaddch(cw->visu.header, raw, 50, ']');
	wnoutrefresh(cw->visu.header);
}

void			vs_checker(t_cw *cw, uint8_t mod)
{
	uint8_t		i;
	uint8_t		raw;

	wattron(cw->visu.header, COLOR_PAIR(10));
	if (mod)
	{
		raw = cw->num_of_champs * 4 + 16;
		mvwprintw(cw->visu.header, raw, 16, "%-10d", cw->cycle_to_die);
		return ;
	}
	i = 0;
	raw = 6;
	while (i < cw->num_of_champs)
		mvwprintw(cw->visu.header, raw += 6, 31,"%5d", cw->champ[i++]->lives);
	wrefresh(cw->visu.header);
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
	if (key == 'q' && cw->visu.delay <= 95)
		cw->visu.delay += 5;
	else if (key == 'w' && cw->visu.delay < 100)
		cw->visu.delay++;
	else if (key == 'r' && cw->visu.delay >= 5)
		cw->visu.delay -= 5;
	else if (key == 'e' && cw->visu.delay >= 1)
		cw->visu.delay--;
    mvwprintw(cw->visu.header, 3, 23, "%5d", 1000 - (cw->visu.delay * 10));
	wrefresh(cw->visu.header);
	wtimeout(cw->visu.menu, cw->visu.delay);
}

void			wait_key(t_cw *cw)
{
	int			key;

	while (1)
		if ((key = wgetch(cw->visu.menu)) == 27)
			visu_exit(cw);
		else if (key == 32 || (key == 's' && !cw->f.lg.pause))
			cw->f.lg.pause = (key == 's' || (key == 32 && !cw->f.lg.pause)) ? 1 : 0;
		else if (key == 'q' || key == 'w' || key == 'e' || key == 'r')
			select_key(cw, key);
		else if (cw->f.lg.pause)
		{
			mvwprintw(cw->visu.header, 1, 1, "%s", "** RUNNIG **");
			wrefresh(cw->visu.header);
		}
		else if (!cw->f.lg.pause || key == 's')
		{
			mvwprintw(cw->visu.header, 1, 1, "%s", "** RUNNIG **");
			wnoutrefresh(cw->visu.header);
			break ;
		}
}