/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/21 17:26:10 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "libft.h"
#include <ncurses.h>

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
		mvwprintw(cw->visu.map, pc * 3 / MAP_X + 1, pc * 3 % MAP_X + 1, "%.2x", cw->map[PCV(pc)]);
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
	mvwprintw(cw->visu.map, pc_prev * 3 / MAP_X + 1, pc_prev * 3 % MAP_X + 1, "%.2x", cw->map[pc_prev]);
	wattron(cw->visu.map, COLOR_PAIR(col * 2));
	mvwprintw(cw->visu.map, pc * 3 / MAP_X + 1, pc * 3 % MAP_X + 1, "%.2x", cw->map[pc]);
	mvwprintw(cw->visu.menu, 4, 10, "y = %3u x = %3u map = %02x pos = %4u, id_car = %u", pc_prev * 3 / MAP_X + 1, pc_prev * 3 % MAP_X + 1, cw->map[pc_prev], pc_prev, i_car + 1);
	mvwprintw(cw->visu.menu, 5, 10, "y = %3u x = %3u map = %02x pos = %4u", pc * 3 / MAP_X + 1, pc * 3 % MAP_X + 1, cw->map[pc], pc);
	wnoutrefresh(cw->visu.menu);
	wnoutrefresh(cw->visu.map);
}

void			vs_backlight_new_car(t_cw *cw, uint8_t col, int32_t pc)
{
	wattron(cw->visu.map, COLOR_PAIR(col * 2));
	mvwprintw(cw->visu.map, pc * 3 / MAP_X + 1, pc * 3 % MAP_X + 1, "%.2x", cw->map[pc]);
	wnoutrefresh(cw->visu.map);
}

void			visu(t_cw *cw)
{
	//int			delay;
	t_stack		*tmp;

	//delay = 5;
	select_key(cw, wgetch(cw->visu.menu));
	wtimeout(cw->visu.menu, cw->visu.delay);
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
