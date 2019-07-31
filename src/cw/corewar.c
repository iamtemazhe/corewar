/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:01:44 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/31 18:57:37 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

static int8_t	dies_checker(t_cw *cw)
{
	if (cw->f.lg.vs)
		vs_print_lives(cw, 1);
	del_cars(cw);
	if (++cw->checks == MAX_CHECKS || cw->lives >= NBR_LIVE)
	{
		cw->cycle_to_die -= CYCLE_DELTA;
		cw->checks = 0;
	}
	cw->lives = 0;
	if (cw->f.lg.vs)
		vs_checker(cw, 1);
	cw->cycle_to_check += cw->cycle_to_die;
	return ((cw->num_of_cars) ? 0 : -1);
}

static void		car_cycler(t_cw *cw)
{
	size_t		i_car;

	cw->f.lg.dbg_cm = 1;
	cw->f.lg.vs_live = 0;
	i_car = cw->num_of_cars;
	while (i_car-- > 0)
	{
		if (!cw->car[i_car]->cycle_to_wait)
		{
			cw->car[i_car]->op_code = cw->map[cw->car[i_car]->pc].v.code;
			if (cw->car[i_car]->op_code < 1 || OP_NUM < cw->car[i_car]->op_code)
			{
				if (cw->f.lg.vs)
					vs_backlight_car(cw, i_car, 1, 1);
				cw->car[i_car]->pc = (cw->car[i_car]->pc + 1) % MEM_SIZE;
				continue ;
			}
			cw->car[i_car]->cycle_to_wait =\
									cw->op[IN(cw->car[i_car]->op_code)].cycles;
		}
		if (!(--cw->car[i_car]->cycle_to_wait))
			cw->op[IN(cw->car[i_car]->op_code)].f(cw, i_car);
	}
}

static void		fight(t_cw *cw)
{
	while (1)
	{
		if (cw->f.lg.vs)
			vs(cw);
		else if (cw->f.lg.dbg &&\
				((cw->f.lg.prg_strt && !cw->f.lg.prg_end &&\
				cw->start_cycle < cw->cycles) ||\
				(cw->f.lg.prg_end && cw->end_cycle < cw->cycles)))
			break ;
		if (cw->f.lg.dump && cw->cycles == cw->cycle_to_dump)
			cw_dump(cw);
		else if (cw->cycle_to_die <= 0 || cw->cycles == cw->cycle_to_check)
			if (dies_checker(cw))
				break ;
		car_cycler(cw);
		cw->cycles++;
	}
}

int				main(int ac, char **av)
{
	t_cw		cw;

	cw_init(&cw);
	cw_map_filler(ac, av, &cw);
	if (cw.f.lg.vs)
		vs_init(&cw);
	add_car(&cw, 0, 0);
	cw_present(&cw);
	fight(&cw);
	cw_results(&cw);
	return (0);
}
