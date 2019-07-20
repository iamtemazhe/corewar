/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:10:38 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/13 19:44:36 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void				vs_log(t_cw *cw, size_t i_car, uint8_t i_op)
{
	if (!i_op)
		return ;
	cw->visu.st_op = st_add(cw, i_car, cw->visu.st_op);
	vs_backlight_map(cw, cw->visu.st_op, 1);
}

void				print_live_breakdown(t_cw *cw, int mod)
{
	uint			k;
	uint			i;
	uint			j;
	uint			total;

	k = (mod < 0) ? 11 + 4 * cw->num_of_champs : 13 + 4 * cw->num_of_champs;
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);
	i = 0;
	total = 0;
	while (i < cw->num_of_champs)
		total = total + cw->champ[i++]->lives;
	i = 1;
	j = 0;
	total = (!total) ? cw->num_of_champs : total;
	mvwprintw(cw->visu.header, k, i, "[");	
	while (++i < 50)
	{
		
		if (i < 48 / total * (3 + cw->champ[j]->lives))
			wattron(cw->visu.header, COLOR_PAIR(j++ * 2 + 1) | A_BOLD);	
		mvwprintw(cw->visu.header, k, i, "-");
	}
	wattron(cw->visu.header, COLOR_PAIR(10) | A_BOLD);	
	mvwprintw(cw->visu.header, k, i, "]");
	wrefresh(cw->visu.header);
}


