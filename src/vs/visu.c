/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/23 13:43:03 by hgysella         ###   ########.fr       */
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
		mvwprintw(cw->visu.map, VPCY(pc), VPCX(pc), "%.2x",\
					cw->map[PCV(pc)].v.code);
		pc++;
	}
	if (mod)
		wattroff(cw->visu.map, A_BOLD);
	wrefresh(cw->visu.map);
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
	mvwprintw(cw->visu.map, VPCY(pc_prev), VPCX(pc_prev), "%.2x",\
				cw->map[pc_prev].v.code);
	wattron(cw->visu.map, COLOR_PAIR(col * 2));
	mvwprintw(cw->visu.map, VPCY(pc), VPCX(pc), "%.2x", cw->map[pc].v.code);
	wrefresh(cw->visu.map);
}

void			vs_backlight_new_car(t_cw *cw, uint8_t col, int32_t pc)
{
	wattron(cw->visu.map, COLOR_PAIR(col * 2));
	mvwprintw(cw->visu.map, VPCY(pc), VPCX(pc), "%.2x", cw->map[pc].v.code);
	mvwprintw(cw->visu.header, 8, 13, "%-6d", cw->num_of_cars);
	wnoutrefresh(cw->visu.map);
	wnoutrefresh(cw->visu.header);
}

void			vs_backlight_del_car(t_cw *cw, uint8_t col, int32_t pc)
{
	wattron(cw->visu.map, COLOR_PAIR(col * 2 - 1));
	mvwprintw(cw->visu.map, VPCY(pc), VPCX(pc), "%.2x", cw->map[pc].v.code);
	mvwprintw(cw->visu.header, 8, 13, "%-6d", cw->num_of_cars);
	wnoutrefresh(cw->visu.map);
	wnoutrefresh(cw->visu.header);
}

void			visu(t_cw *cw)
{
	t_stack		*tmp;

	wait_key(cw);
	print_cycles(cw);
	doupdate();
	if (cw->visu.st_op)
	{
		tmp = cw->visu.st_op->prev;
		while (tmp)
		{
			tmp = tmp->prev;
			if (cw->cycles - tmp->cycle_to_show >= CYCLE_TO_SHOW)
			{
				vs_backlight_map(cw, tmp, 0);
				st_del(&tmp);
			}
			else
				break ;
		}
		if (!tmp)
			cw->visu.st_op = tmp;
	}
}
