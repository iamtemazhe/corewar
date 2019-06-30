/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 18:21:42 by jwinthei          #+#    #+#             */
/*   Updated: 2019/06/14 18:22:27 by jwinthei         ###   ########.fr       */
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
		.description = "alive",
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
		.description = "load",
		.codage = 1,
		.label_size = 4,
		.f = &op_ld
	},
	{
		.name = "st",
		.num_args = 2,
		.args = {T_REG, T_IND | T_REG},
		.code = 3,
		.cycles = 5,
		.description = "store",
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
		.description = "addition",
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
		.description = "soustraction",
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
		.description = "et (and  r1, r2, r3   r1&r2 -> r3",
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
		.description = "ou  (or   r1, r2, r3   r1 | r2 -> r3",
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
		.description = "ou (xor  r1, r2, r3   r1^r2 -> r3",
		.codage = 1,
		.label_size = 4,
		.f = &op_xor
	},
	{
		.name = "zjmp",
		.num_args = 1,
		.args = {T_DIR},
		.code = 9,
		.cycles = 20,
		.description = "jump if zero",
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
		.description = "load index",
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
		.description = "store index",
		.codage = 1,
		.label_size = 2,
		.f = &op_sti
	},
	{
		.name = "fork",
		.num_args = 1,
		.args = {T_DIR},
		.code = 12,
		.cycles = 800,
		.description = "fork",
		.codage = 0,
		.label_size = 2,
		.f = &op_fork
	},
	{
		.name = "lld",
		.num_args = 2,
		.args = {T_DIR | T_IND, T_REG},
		.code = 13,
		.cycles = 10,
		.description = "long load",
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
		.description = "long load index",
		.codage = 1,
		.label_size = 2,
		.f = &op_lldi
	},
	{
		.name = "lfork",
		.num_args = 1,
		.args = {T_DIR},
		.code = 15,
		.cycles = 1000,
		.description = "long fork",
		.codage = 0,
		.label_size = 2,
		.f = &op_lfork
	},
	{
		.name = "aff",
		.num_args = 1,
		.args = {T_REG},
		.code = 16,
		.cycles = 2,
		.description = "aff",
		.codage = 1,
		.label_size = 4,
		.f = &op_aff
	}
};
#endif
