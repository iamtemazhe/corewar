/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:01:27 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/31 17:06:04 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_tab.h"
#include "cw.h"

void				cw_init(t_cw *cw)
{
	cw->car = NULL;
	cw->champ = NULL;
	ft_bzero(cw->map, sizeof(*cw->map) * MEM_SIZE);
	ft_bzero(cw->arg, sizeof(*cw->arg) * OP_NUM_ARGS);
	ft_bzero(cw->arg_code, sizeof(*cw->arg_code) * OP_NUM_ARGS);
	cw->f.lag = 0;
	cw->num_of_champs = 0;
	cw->err = 0;
	cw->lives = 0;
	cw->vs.champs_lives = 0;
	cw->last_live_champ_i = 1;
	cw->checks = 0;
	cw->cycles = 0;
	cw->start_cycle = 0;
	cw->cycle_to_die = CYCLE_TO_DIE;
	cw->cycle_to_check = CYCLE_TO_DIE;
	cw->cycle_to_dump = 0;
	cw->step = 0;
	cw->pos = 0;
	cw->op = g_op;
}
