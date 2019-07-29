/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 18:21:42 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/29 19:43:08 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_TAB_H
# define OP_TAB_H

# include "cw.h"

t_op							g_op[OP_NUM] = {
	{
		.name = "live",
		.num_args = 1,
		.args = {T_DIR, 0, 0},
		.code = 1,
		.cycles = 10,
		.codage = 0,
		.label_size = 4,
		.f = &op_live
	},
	{
		.name = "ld",
		.num_args = 2,
		.args = {T_DIR | T_IND, T_REG, 0},
		.code = 2,
		.cycles = 5,
		.codage = 1,
		.label_size = 4,
		.f = &op_ld
	},
	{
		.name = "st",
		.num_args = 2,
		.args = {T_REG, T_IND | T_REG, 0},
		.code = 3,
		.cycles = 5,
		.codage = 1,
		.label_size = 4,
		.f = &op_st
	},
	{
		.name = "add",
		.num_args = 3,
		.args = {T_REG, T_REG, T_REG},
		.code = 4,
		.cycles = 10,
		.codage = 1,
		.label_size = 4,
		.f = &op_add
	},
	{
		.name = "sub",
		.num_args = 3,
		.args = {T_REG, T_REG, T_REG},
		.code = 5,
		.cycles = 10,
		.codage = 1,
		.label_size = 4,
		.f = &op_sub
	},
	{
		.name = "and",
		.num_args = 3,
		.args = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.code = 6,
		.cycles = 6,
		.codage = 1,
		.label_size = 4,
		.f = &op_and
	},
	{
		.name = "or",
		.num_args = 3,
		.args = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.code = 7,
		.cycles = 6,
		.codage = 1,
		.label_size = 4,
		.f = &op_or
	},
	{
		.name = "xor",
		.num_args = 3,
		.args = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.code = 8,
		.cycles = 6,
		.codage = 1,
		.label_size = 4,
		.f = &op_xor
	},
	{
		.name = "zjmp",
		.num_args = 1,
		.args = {T_DIR, 0, 0},
		.code = 9,
		.cycles = 20,
		.codage = 0,
		.label_size = 2,
		.f = &op_zjmp
	},
	{
		.name = "ldi",
		.num_args = 3,
		.args = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.code = 10,
		.cycles = 25,
		.codage = 1,
		.label_size = 2,
		.f = &op_ldi
	},
	{
		.name = "sti",
		.num_args = 3,
		.args = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.code = 11,
		.cycles = 25,
		.codage = 1,
		.label_size = 2,
		.f = &op_sti
	},
	{
		.name = "fork",
		.num_args = 1,
		.args = {T_DIR, 0, 0},
		.code = 12,
		.cycles = 800,
		.codage = 0,
		.label_size = 2,
		.f = &op_fork
	},
	{
		.name = "lld",
		.num_args = 2,
		.args = {T_DIR | T_IND, T_REG, 0},
		.code = 13,
		.cycles = 10,
		.codage = 1,
		.label_size = 4,
		.f = &op_lld
	},
	{
		.name = "lldi",
		.num_args = 3,
		.args = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.code = 14,
		.cycles = 50,
		.codage = 1,
		.label_size = 2,
		.f = &op_lldi
	},
	{
		.name = "lfork",
		.num_args = 1,
		.args = {T_DIR, 0, 0},
		.code = 15,
		.cycles = 1000,
		.codage = 0,
		.label_size = 2,
		.f = &op_lfork
	},
	{
		.name = "aff",
		.num_args = 1,
		.args = {T_REG, 0, 0},
		.code = 16,
		.cycles = 2,
		.codage = 1,
		.label_size = 4,
		.f = &op_aff
	}
};
#endif
