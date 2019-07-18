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
