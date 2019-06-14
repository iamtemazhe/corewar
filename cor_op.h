/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_op.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:08:48 by jwinthei          #+#    #+#             */
/*   Updated: 2019/06/12 19:43:45 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COR_OP_H
# define COR_OP_H

# include <stdint.h>
# include "libft.h"
# include "op.h"

# define COMMENT_CHAR_ALT       ';'
# define OP_num_args			(3)
# define N						0x1
# define DUMP					0x2
# define VISU					0x4

# include "op.h"
// typedef struct					s_visu
// {

// }								t_visu;

typedef struct					s_champ
{
	header_t					head;
	uint8_t						id;
	uint8_t						state;
	uint8_t						*exec;
	struct s_champ				*next;
}								t_champ;

typedef struct					s_cw
{
//	t_visu						visu;
	t_champ						*champ;
	uint8_t						map[MEM_SIZE];
	uint32_t					num_champs;
	uint8_t						flg;
	uint32_t					cycles;
	uint32_t					num_check;
	uint32_t					cycles_check;
	int							cycles_to_die;
}								t_cw;

typedef struct					s_car
{
	uint8_t						id;
	uint8_t						carry;
	uint32_t					op_code;	
	uint32_t					last_live;
	uint32_t					wait_cycles;
	uint32_t					pos;
	uint32_t					step;
	uint32_t					reg[REG_NUMBER];
}								t_car;

typedef struct					s_op
{
	char						*name;
	uint8_t						num_args;
	uint8_t						args[OP_num_args];
	uint8_t						code;
	uint32_t					cycles;
	char						*description;
	uint8_t						codage;
	uint8_t						label_size;
	void						(*f)(t_cw *, t_car *);
}								t_op;

void							op_live(t_cw *cw, t_car *car);
void							parse_args(int ac, char **av, t_cw *cw);
//void							fill_cw(int ac, char **av, t_cw *cw);
void							fill_champ_id(t_cw *cw);
void							error_func(char *str);
void							fill_map(t_cw *cw);

// t_op							g_op[16] = {
// 	{
// 		.name = "live",
// 		.num_args = 1,
// 		.args = {T_DIR, 0, 0},
// 		.code = 1,
// 		.cycles = 10,
// 		.description = "alive",
// 		.codage = 0,
// 		.label_size = 4,
// 		.f = &op_live
// 	},
// 	{
// 		.name = "ld",
// 		.num_args = 2,
// 		.args = {T_DIR | T_IND, T_REG, 0},
// 		.code = 2,
// 		.cycles = 5,
// 		.description = "load",
// 		.codage = 1,
// 		.label_size = 4,
// 		.f = &op_ld
// 	},
// 	{
// 		.name = "st",
// 		.num_args = 2,
// 		.args = {T_REG, T_IND | T_REG},
// 		.code = 3,
// 		.cycles = 5,
// 		.description = "store",
// 		.codage = 1,
// 		.label_size = 4,
// 		.f = &op_st
// 	},
// 	{
// 		.name = "add",
// 		.num_args = 3,
// 		.args = {T_REG, T_REG, T_REG},
// 		.cycles = 4,
// 		.cycles = 10,
// 		.description = "addition",
// 		.code = 1,
// 		.label_size = 4,
// 		.f = &op_add
// 	},
// 	{
// 		.name = "sub",
// 		.num_args = 3,
// 		.args = {T_REG, T_REG, T_REG},
// 		.code = 5,
// 		.cycles = 10,
// 		.description = "soustraction",
// 		.codage = 1,
// 		.label_size = 4,
// 		.f = &op_sub
// 	},
// 	{
// 		.name = "and",
// 		.num_args = 3,
// 		.args = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
// 		.code = 6,
// 		.cycles = 6,
// 		"et (and  r1, r2, r3   r1&r2 -> r3",
// 		.codage = 1,
// 		.label_size = 4,
// 		.f = &op_and
// 	},
// 	{
// 		.name = "or",
// 		.num_args = 3,
// 		.args = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
// 		.code = 7,
// 		.cycles = 6,
// 		.description = "ou  (or   r1, r2, r3   r1 | r2 -> r3",
// 		.codage = 1,
// 		.label_size = 4,
// 		.f = &op_or
// 	},
// 	{
// 		.name = "xor",
// 		.num_args = 3,
// 		.args = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
// 		.code = 8,
// 		.cycles = 6,
// 		.description = "ou (xor  r1, r2, r3   r1^r2 -> r3",
// 		.codage = 1,
// 		.label_size = 4,
// 		.f = &op_xor
// 	},
// 	{
// 		.name = "zjmp",
// 		.num_args = 1,
// 		.args = {T_DIR},
// 		.code = 9,
// 		.cycles = 20,
// 		.description = "jump if zero",
// 		.codage = 0,
// 		.label_size = 2,
// 		.f = &op_zjmp
// 	},
// 	{
// 		.name = "ldi",
// 		.num_args = 3,
// 		.args = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
// 		.code = 10,
// 		.cycles = 25,
// 		.description = "load index",
// 		.codage = 1,
// 		.label_size = 2,
// 		.f = &op_ldi
// 	},
// 	{
// 		.name = "sti",
// 		.num_args = 3,
// 		.args = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
// 		.code = 11,
// 		.cycles = 25,
// 		.description = "store index",
// 		.codage = 1,
// 		.label_size = 2,
// 		.f = &op_sti
// 	},
// 	{
// 		.name = "fork",
// 		.num_args = 1,
// 		.args = {T_DIR},
// 		.code = 12,
// 		.cycles = 800,
// 		.description = "fork",
// 		.codage = 0,
// 		.label_size = 2,
// 		.f = &op_fork
// 	},
// 	{
// 		.name = "lld",
// 		.num_args = 2,
// 		.args = {T_DIR | T_IND, T_REG},
// 		.code = 13,
// 		.cycles = 10,
// 		.description = "long load",
// 		.codage = 1,
// 		.label_size = 4,
// 		.f = &op_lld
// 	},
// 	{
// 		.name = "lldi",
// 		.num_args = 3,
// 		.args = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
// 		.code = 14,
// 		.cycles = 50,
// 		.description = "long load index",
// 		.codage = 1,
// 		.label _size = 2,
// 		.f = &op_lldi
// 	},
// 	{
// 		.name = "lfork",
// 		.num_args = 1,
// 		.args = {T_DIR},
// 		.code = 15,
// 		.cycles = 1000,
// 		.description = "long fork",
// 		.codage = 0,
// 		.label_size = 2,
// 		.f = &op_lfork
// 	},
// 	{
// 		.name = "aff",
// 		.num_args = 1,
// 		.args = {T_REG},
// 		.code = 16,
// 		.cycles = 2,
// 		.description = "aff",
// 		.codage = 1,
// 		.label_size = 4,
// 		.f = &op_aff
// 	}
// };
#endif
