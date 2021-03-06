/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_codage_validator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 15:03:57 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/31 18:58:22 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

static void			reg(t_cw *cw, uint8_t i_arg, size_t i_car, uint8_t i_op)
{
	cw->step += REGN_SIZE;
	if (!(cw->op[i_op].args[i_arg] & T_REG))
		cw->err = -1;
	if (cw->err)
		return ;
	cw->pos = cw->car[i_car]->pc + cw->step;
	cw->arg_code[i_arg] = cw->map[PC(cw->pos)].v.code;
	if (1 <= cw->arg_code[i_arg] && cw->arg_code[i_arg] <= REG_NUMBER)
		cw->arg[i_arg] = cw->arg_code[i_arg] - 1;
	else
		cw->err = -1;
}

static void			ind(t_cw *cw, uint8_t i_arg, size_t i_car, uint8_t i_op)
{
	cw->step += IND_SIZE;
	if (!(cw->op[i_op].args[i_arg] & T_IND))
		cw->err = -1;
	if (cw->err)
		return ;
	cw->pos = PCV(cw->car[i_car]->pc + cw->step);
	cw->arg[i_arg] = cw_code_to_byte(cw->map, cw->pos, IND_SIZE);
	cw->arg_code[i_arg] = cw->arg[i_arg];
	if (i_op == LLD)
		cw->arg[i_arg] = PCV(cw->arg[i_arg] + cw->car[i_car]->pc);
	else
		cw->arg[i_arg] = PCV(cw->arg[i_arg] % IDX_MOD + cw->car[i_car]->pc);
	if (i_op == ST)
		return ;
	cw->arg[i_arg] = cw_code_to_byte(cw->map, PCV(cw->arg[i_arg]), REG_SIZE);
}

static void			dir(t_cw *cw, uint8_t i_arg, size_t i_car, uint8_t i_op)
{
	cw->step += cw->op[i_op].label_size;
	if (!(cw->op[i_op].args[i_arg] & T_DIR))
		cw->err = -1;
	if (cw->err)
		return ;
	cw->pos = PCV(cw->car[i_car]->pc + cw->step);
	cw->arg[i_arg] = cw_code_to_byte(cw->map, cw->pos,\
											cw->op[i_op].label_size);
	cw->arg_code[i_arg] = cw->arg[i_arg];
}

int8_t				cw_codage_validator(t_cw *cw, size_t i_car, uint8_t i_op)
{
	int8_t			i_arg;
	uint8_t			code;

	cw->step = OPC_SIZE;
	cw->cod.age = cw->map[PC(cw->car[i_car]->pc + cw->step)].v.code;
	cw->err = (cw->cod.arg.v4) ? -1 : 0;
	i_arg = -1;
	while (++i_arg < cw->op[i_op].num_args)
		if (!(code = (cw->cod.age >> (6 - i_arg * 2)) & 0x3))
			cw->err = -1;
		else if (code == IND_CODE)
			ind(cw, i_arg, i_car, i_op);
		else if (code == REG_CODE)
			reg(cw, i_arg, i_car, i_op);
		else
			dir(cw, i_arg, i_car, i_op);
	if (cw->f.lg.vs)
		vs_backlight_car(cw, i_car, cw->step, 1);
	else if (cw->f.lg.dbg)
		dbg_log_cod(cw, i_car);
	if (!cw->err)
		return (0);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	cw->err = 0;
	return (-1);
}
