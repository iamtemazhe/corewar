/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:05:10 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/30 15:37:58 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

inline static void	usage(char *prog_name)
{
	ft_printf("\033[1;30mUsage: %s [-dump N | -dump64 N] [-d | -dc | -v] [-a] [-n N] <champion.cor> <...>\n", prog_name);
	ft_printf("*********************** PROGRAMM FLAGS ********************************\n");
	ft_printf("| -a            : Prints output from \"aff\" (default is to hide it)    |\n");
	ft_printf("| -n N <*.cor>  : Sets champion number (from 1) for <champion.cor>    |\n");
	ft_printf("********************* TEXT OUTPUT MODE ********************************\n");
	ft_printf("| -dump N       : Dumps memory by 32 octets after N cycles then exits |\n");
	ft_printf("| -dump64 N     : Dumps memory by 64 octets after N cycles then exits |\n");
	ft_printf("********************* vsAL OUTPUT MODE ******************************\n");
	ft_printf("| -d            : Debug mode                                          |\n");
	ft_printf("| -dc           : Debug mode with cycles                              |\n");
	ft_printf("| -dr           : Debug mode with car death                           |\n");
	ft_printf("| -df           : Debug mode with all modifications                   |\n");
	ft_printf("| -v            : visual (by Ncurses) output mode                     |\n");
	ft_printf("***********************************************************************\033[0m\n");
}

void				cw_out(t_cw *cw, int prnt, char *prog_name)
{
	if (prog_name)
		usage(prog_name);
	if (cw->f.lg.vs)
	{
		delwin(cw->vs.aff);
		delwin(cw->vs.map);
		delwin(cw->vs.header);
		delwin(cw->vs.bkg);
		endwin();
	}
	cw->cycle_to_die = 0;
	del_cars(cw);
	del_all_champs(cw);
	exit((prnt) ? -1 : 0);
}


void				cw_present(t_cw *cw)
{
	uint8_t		i_champ;

	if (cw->f.lg.dbg)
		dbg_log_table(0);
	if (cw->f.lg.vs || cw->f.lg.dbg)
		return ;
	ft_printf("Introducing contestants...\n");
	i_champ = 0;
	while (i_champ < cw->num_of_champs)
	{
		ft_printf("* Player %u, weighing %u bytes, \"%s\" (\"%s\") !\n",\
				cw->champ[i_champ]->id, cw->champ[i_champ]->head.prog_size,\
				cw->champ[i_champ]->head.prog_name, cw->champ[i_champ]->head.comment);
		i_champ++;
	}
}

void			cw_results(t_cw *cw)
{
	if (cw->f.lg.dbg)
		dbg_log_table(1);
	else if (cw->f.lg.vs)
		vs_out(cw);
	else
		ft_printf("Contestant %u, \"%s\", has won !\n",\
			cw->last_live_id, cw->champ[cw->last_live_id - 1]->head.prog_name);
}

void			cw_dump(t_cw *cw)
{
	int32_t		i;
	uint8_t		num_of_oct;

	i = 0;
	num_of_oct = (cw->f.lg.dump64) ? 64 : 32;
	while (i < MEM_SIZE)
	{
		if (!(i % num_of_oct))
			ft_printf("0x%04zx : ", i);
		ft_printf("%02x%c", cw->map[i].v.code,\
				((i % num_of_oct) == num_of_oct - 1) ? '\n' : ' ');
		i++;
	}
	cw_out(cw, 0, 0);
}
