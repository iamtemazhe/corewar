/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:24:32 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/18 17:16:13 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_H
# define CW_H

# include "op.h"
# include "libft.h"
# include "stack.h"
# include <ncurses.h>

# define N						0x1
# define DUMP					0x2
# define VISU					0x4
# define DEBUG					0x8

# define CYCLE_TO_SHOW			50

# define OP_SIZE				1
# define CODAGE_SIZE		    1
# define REGN_SIZE		  		1
# define OP_NUM				    16
# define OP_NUM_ARGS			3
# define OPC_SIZE				OP_SIZE + CODAGE_SIZE

# define LIVE					0
# define LD						1
# define ST						2
# define ADD					3
# define SUB					4
# define AND					5
# define OR 					6
# define XOR					7
# define ZJMP					8
# define LDI					9
# define STI					10
# define FORK					11
# define LLD					12
# define LLDI					13
# define LFORK					14
# define AFF					15

# define IN(x)					((x) ? ((x) - 1) : (x))
# define PCV(x)					((x) % MEM_SIZE)
# define PC(x)					(PCV(IN(x)))

typedef struct					s_visu
{
	WINDOW						*map;
	WINDOW						*header;
	WINDOW						*menu;
	WINDOW						*bkg;
	uint						row;
	uint						col;
	t_stack						*st_op;
}								t_visu;

typedef struct					s_champ
{
	header_t					head;
	uint8_t						id;
	uint8_t						*exec;
	uint32_t					lives;
}								t_champ;

typedef struct					s_car
{
	uint8_t						id;
	uint8_t						carry;
	uint32_t					op_code;
	uint32_t					last_live;
	uint32_t					cycle_to_wait;
	uint32_t					pc;
	uint32_t					reg[REG_NUMBER];
}								t_car;

typedef struct s_cw				t_cw;

typedef struct					s_op
{
	char						*name;
	uint8_t						num_args;
	uint8_t						args[OP_NUM_ARGS];
	uint8_t						code;
	uint32_t					cycles;
	char						*description;
	uint8_t						codage;
	uint8_t						label_size;
	void						(*f)(t_cw *, uint8_t);
}								t_op;

struct							s_cw
{
	t_visu						visu;
	t_champ						*champ;
	t_car						**car;
	int8_t						err;
	uint8_t						flg;
	uint8_t						map[MEM_SIZE];
	uint32_t					num_of_champs;
	uint32_t					num_of_cars;
	uint32_t					lives;
	uint32_t					checks;
	uint32_t					cycles;
	uint32_t					cycle_to_die;
	uint32_t					cycle_to_dump;
	uint32_t					cycle_to_check;
	uint32_t					step;
	uint32_t					pos;
	uint32_t					arg[OP_NUM_ARGS];
	uint32_t					arg_code[OP_NUM_ARGS];
	t_op						*op;
	union
	{
		uint8_t					age;
		struct
		{	
			unsigned			v4 : 2;
			unsigned			v3 : 2;
			unsigned			v2 : 2;
			unsigned			v1 : 2;
		}						arg;
	}							cod;
};

void							op_live(t_cw *cw, uint8_t i_car);
void							op_ld(t_cw *cw, uint8_t i_car);
void							op_st(t_cw *cw, uint8_t i_car);
void							op_st(t_cw *cw, uint8_t i_car);
void							op_add(t_cw *cw, uint8_t i_car);
void							op_sub(t_cw *cw, uint8_t i_car);
void							op_and(t_cw *cw, uint8_t i_car);
void							op_or(t_cw *cw, uint8_t i_car);
void							op_xor(t_cw *cw, uint8_t i_car);
void							op_zjmp(t_cw *cw, uint8_t i_car);
void							op_ldi(t_cw *cw, uint8_t i_car);
void							op_sti(t_cw *cw, uint8_t i_car);
void							op_fork(t_cw *cw, uint8_t i_car);
void							op_lld(t_cw *cw, uint8_t i_car);
void							op_lldi(t_cw *cw, uint8_t i_car);
void							op_lfork(t_cw *cw, uint8_t i_car);
void							op_aff(t_cw *cw, uint8_t i_car);

size_t							code_to_byte(const void *src, size_t pos,\
																	size_t n);
void							byte_to_code(void *dst, size_t pos,\
													const void *src, size_t n);
int8_t							codage_validator(t_cw *cw, uint8_t i_car,
																uint8_t i_op);
void							fill_cw(int ac, char **av, t_cw *cw);
int								ft_strrstr(const char *haystack, const char *needle);
void							vs_log(t_cw *cw, uint8_t i_car, uint8_t i_op);
void							dbg_log(t_cw *cw, uint8_t i_car);
void							dbg_log_cod(t_cw *cw, uint8_t i_car);
void							dbg_log_top();
void							dbg_log_bot();

void							init_cw(t_cw *cw);
uint8_t							add_car(t_cw *cw, uint8_t i_car);
void							del_car(t_cw *cw, uint8_t i_car);
void							del_all_cars(t_cw *cw);

void							visu(t_cw *cw);
void							init_visu(t_cw *cw);
void							select_key(t_cw *cw, int key, int *delay);

#endif
