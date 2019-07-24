/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/24 13:27:12 by hgysella         ###   ########.fr       */
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
	//wattron(cw->visu.map, COLOR_PAIR(st_op->id * 2 + 7) | A_BOLD);
	if (!mod)
		wattroff(cw->visu.map, A_BOLD);
	while (++i <= st_op->size)
	{
		mvwprintw(cw->visu.map, VPCY(pc), VPCX(pc), "%.2x",\
					cw->map[pc].v.code);
		cw->map[pc].v.col = st_op->id * 2 - 1; 	
		pc = PCV(pc + 1);
	}
	if (mod)
		wattroff(cw->visu.map, A_BOLD);
	// wnoutrefresh(cw->visu.map);
}

void			vs_backlight_car(t_cw *cw, size_t i_car, int32_t step)
{
	uint8_t		col;
	uint32_t	pc_prev;
	uint32_t	pc;

	pc_prev = cw->car[i_car]->pc;
	pc = PCV(pc_prev + step);
	//col = (cw->map[pc_prev].v.col) ? cw->map[pc_prev].v.col + 1 : -cw->car[i_car]->reg[0] * 2;
	col = (cw->map[pc].v.col) ? cw->map[pc].v.col + 1 : -cw->car[i_car]->reg[0] * 2;
	// if (--cw->map[pc_prev].v.car)
	// {
	// 	if (cw->map[pc_prev].v.live)
	// 		wattron(cw->visu.map, COLOR_PAIR((cw->map[pc_prev].v.col + 8) | A_BOLD));
	// 	else
	// 		wattron(cw->visu.map, COLOR_PAIR(cw->map[pc_prev].v.col + 1) |\
	// 							(cw->map[pc_prev].v.bold) ? A_BOLD : 0);
	// 	mvwprintw(cw->visu.map, VPCY(pc_prev), VPCX(pc_prev), "%.2x",\
	// 				cw->map[pc_prev].v.code);
	// }
	if (!(--cw->map[pc_prev].v.car) && !cw->map[pc_prev].v.live)
	{
		wattron(cw->visu.map, COLOR_PAIR(cw->map[pc_prev].v.col));
		mvwprintw(cw->visu.map, VPCY(pc_prev), VPCX(pc_prev), "%.2x",\
					cw->map[pc_prev].v.code);
	}
	cw->map[pc].v.car++;
	if (cw->map[pc].v.live)
		wattron(cw->visu.map, COLOR_PAIR((cw->map[pc_prev].v.col + 8) | A_BOLD));
	else
		wattron(cw->visu.map, COLOR_PAIR(col));
	mvwprintw(cw->visu.map, VPCY(pc), VPCX(pc), "%.2x", cw->map[pc].v.code);
	// woutrefresh(cw->visu.map);
}

void			vs_backlight_new_car(t_cw *cw, u_int8_t col, int32_t pc)
{
	wattron(cw->visu.map, COLOR_PAIR((cw->map[pc].v.col) ? cw->map[pc].v.col + 1 : col * 2));	
	cw->map[pc].v.car++;
	if (!cw->map[pc].v.live)
	{
		mvwprintw(cw->visu.map, VPCY(pc), VPCX(pc), "%.2x", cw->map[pc].v.code);
		// wnoutrefresh(cw->visu.map);
	}
	mvwprintw(cw->visu.header, 8, 13, "%-6d", cw->num_of_cars);
	// wnoutrefresh(cw->visu.header);
}

void			vs_backlight_del_car(t_cw *cw, int32_t pc)
{
	wattron(cw->visu.map, COLOR_PAIR(cw->map[pc].v.col));
	if (--cw->map[pc].v.car)
	{
		mvwprintw(cw->visu.map, VPCY(pc), VPCX(pc), "%.2x", cw->map[pc].v.code);
		// wnoutrefresh(cw->visu.map);
	}
	mvwprintw(cw->visu.header, 8, 13, "%-6d", cw->num_of_cars);
	// wnoutrefresh(cw->visu.header);
}

void			visu(t_cw *cw)
{
	// t_stack		*tmp;

	wattron(cw->visu.header, COLOR_PAIR(15) | A_BOLD);
	wait_key(cw);
	print_cycles(cw);
	if (cw->f.lg.vs_live)
		print_lives(cw, 0);
	wnoutrefresh(cw->visu.map);
	wnoutrefresh(cw->visu.header);
	doupdate();
	// if (cw->visu.st_op)
	// {
	// 	tmp = cw->visu.st_op->prev;
	// 	while (tmp)
	// 	{
	// 		tmp = tmp->prev;
	// 		if (cw->cycles - tmp->cycle_to_show >= CYCLE_TO_SHOW)
	// 		{
	// 			vs_backlight_map(cw, tmp, 0);
	// 			st_del(&tmp);
	// 		}
	// 		else
	// 			break ;
	// 	}
	// 	if (!tmp)
	// 		cw->visu.st_op = tmp;
	// }
}
