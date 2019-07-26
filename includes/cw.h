/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:24:32 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/26 19:07:08 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_H
# define CW_H

# include "op.h"
# include "libft.h"
# include <ncurses.h>

# define AF						0x01
# define DUMP					0x02
# define VISU					0x04
# define DEBUG					0x08
# define PAUSE					0x10 | vs
# define DUMP64					0x20 | DUMP
# define DEBUG_C				0x40 | DEBUG
# define DEBUG_R				0x80 | DEBUG
# define DEBUG_F				DEBUG | DEBUG_C | DEBUG_R
# define VS_LIVE				0x100

# define CYCLE_TO_SHOW			50
# define LIVES_TO_SHOW			50
# define MAP_X					192

# define COLOR_BRIGHT			0x8
# define COLOR_GRAY				COLOR_BLACK | COLOR_BRIGHT
# define COLOR_B_WHITE			COLOR_WHITE | COLOR_BRIGHT
# define COL_CODE_CH1			1
# define COL_CODE_CH2			2
# define COL_CODE_CH3			3
# define COL_CODE_CH4			4
# define COL_CODE				5
# define COL_BACK_CH1			6
# define COL_BACK_CH2			7
# define COL_BACK_CH3			8
# define COL_BACK_CH4			9
# define COL_BACK				10
# define COL_LIVE_CODE_CH1		11
# define COL_LIVE_CODE_CH2		12
# define COL_LIVE_CODE_CH3		13
# define COL_LIVE_CODE_CH4		14
# define COL_GRAY_WHITE			15
# define COL_LIVE_CAR_CH1		16
# define COL_LIVE_CAR_CH2		17
# define COL_LIVE_CAR_CH3		18
# define COL_LIVE_CAR_CH4		19
# define COL_TEXT				20
# define COL_STEP				COL_BACK - COL_CODE
# define COL_LIVE_STEP			COL_LIVE_CODE_CH1 - COL_CODE_CH1

# define MAGIC_HEADER_SIZE		4
# define DELIMETR_SIZE			4
# define CHAMP_EXEC_SIZE		4
# define HEADER_SIZE			PROG_NAME_LENGTH + COMMENT_LENGTH + MAGIC_HEADER_SIZE +\
								(2 * DELIMETR_SIZE) + CHAMP_EXEC_SIZE

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

# define ABS(x)					(((int8_t)(x)) < 0 ? (-x) : (x))
# define IN(x)					((x) ? ((x) - 1) : (x))
# define PCV(x)					((((x) < 0) ? (MEM_SIZE - -(x)) : (x)) % MEM_SIZE)
# define PC(x)					(PCV(IN(x)))
# define VPCY(x)				((x) * 3 / MAP_X + 1)
# define VPCX(x)				((x) * 3 % MAP_X + 1)

typedef struct					s_vs
{
	WINDOW						*map;
	WINDOW						*header;
	WINDOW						*menu;
	WINDOW						*bkg;
	uint32_t					delay;
}								t_vs;

typedef struct					s_champ
{
	header_t					head;
	uint8_t						id;
	uint8_t						*exec;
	uint32_t					lives;
	size_t						last_live;
}								t_champ;

typedef struct					s_car
{
	uint8_t						carry;
	uint8_t						op_code;
	int32_t						pc;
	int32_t						reg[REG_NUMBER];
	size_t						id;
	size_t						last_live;
	size_t						cycle_to_wait;
}								t_car;

typedef struct s_cw				t_cw;

typedef struct					s_op
{
	char						*name;
	uint8_t						num_args;
	uint8_t						args[OP_NUM_ARGS];
	uint8_t						code;
	size_t						cycles;
	uint8_t						codage;
	uint8_t						label_size;
	void						(*f)(t_cw *, size_t);
}								t_op;

struct							s_cw
{
	t_vs						vs;
	t_op						*op;
	t_car						**car;
	t_champ						**champ;
	int8_t						err;
	uint8_t						flg;
	uint8_t						checks;
	uint8_t						num_of_champs;
	int32_t						pos;
	int32_t						step;
	int32_t						cycle_to_die;
	int32_t						arg[OP_NUM_ARGS];
	uint32_t					lives;
	uint32_t					arg_code[OP_NUM_ARGS];
	size_t						last_live_id;
	size_t						cycles;
	size_t						cycle_to_dump;
	size_t						cycle_to_check;
	size_t						num_of_cars;
	size_t						max_num_of_cars;
		union
	{
		uint16_t				lag;
		struct
		{	
			uint8_t				af		: 1;
			uint8_t				dump	: 1;
			uint8_t				vs		: 1;
			uint8_t				dbg		: 1;
			uint8_t				pause	: 1;
			uint8_t				dump64	: 1;
			uint8_t				dbg_c	: 1;
			uint8_t				dbg_cm	: 1;
			uint8_t				dbg_r	: 1;
			uint8_t				vs_live	: 1;
		}						lg;
	}							f;
	union
	{
		uint8_t					age;
		struct
		{	
			uint8_t				v4 : 2;
			uint8_t				v3 : 2;
			uint8_t				v2 : 2;
			uint8_t				v1 : 2;
		}						arg;
	}							cod;
	union						u_map
	{
	    uint32_t				val;
	    struct
	    {
	        uint8_t				code	: 8;
	        uint8_t				col		: 3;
	        uint8_t				live	: 1;
	        uint8_t				bold	: 6;
	        uint16_t			car		: 14;
	    }						v;
	}							map[MEM_SIZE];
};

void							op_live(t_cw *cw, size_t i_car);
void							op_ld(t_cw *cw, size_t i_car);
void							op_st(t_cw *cw, size_t i_car);
void							op_st(t_cw *cw, size_t i_car);
void							op_add(t_cw *cw, size_t i_car);
void							op_sub(t_cw *cw, size_t i_car);
void							op_and(t_cw *cw, size_t i_car);
void							op_or(t_cw *cw, size_t i_car);
void							op_xor(t_cw *cw, size_t i_car);
void							op_zjmp(t_cw *cw, size_t i_car);
void							op_ldi(t_cw *cw, size_t i_car);
void							op_sti(t_cw *cw, size_t i_car);
void							op_fork(t_cw *cw, size_t i_car);
void							op_lld(t_cw *cw, size_t i_car);
void							op_lldi(t_cw *cw, size_t i_car);
void							op_lfork(t_cw *cw, size_t i_car);
void							op_aff(t_cw *cw, size_t i_car);

size_t							code_to_byte(const union u_map *src, int32_t pos, size_t n);
void							byte_to_code(union u_map *dst, int32_t pos, const void *src, size_t n);

int8_t							codage_validator(t_cw *cw, size_t i_car, uint8_t i_op);
void							cw_fill(int ac, char **av, t_cw *cw);
int								ft_strrstr(const char *haystack, const char *needle);

void							cw_init(t_cw *cw);
void							dbg_log(t_cw *cw, size_t i_car);
void							dbg_log_cod(t_cw *cw, size_t i_car);
void							dbg_log_top();
void							dbg_log_bot();
void							dump(t_cw *cw);
void							present(t_cw *cw);
void							results(t_cw *cw);
void							usage(int prnt, char *prog_name);

uint8_t							add_car(t_cw *cw, size_t i_car, int32_t pc);
void							del_cars(t_cw *cw);

int8_t							add_champ(t_cw *cw, uint8_t id_champ);

void							vs(t_cw *cw);
void							vs_out(t_cw *cw);
void							vs_init(t_cw *cw);
void							vs_exit(t_cw *cw);
void							vs_print_windows(t_cw *cw);
void							vs_log(t_cw *cw, size_t i_car, int32_t pc);
void							vs_backlight_on_car(t_cw *cw, uint8_t col, int32_t pc, uint8_t mod);
void							vs_backlight_car(t_cw *cw, size_t i_car, int32_t step, uint8_t mod);
void							vs_backlight_del_car(t_cw *cw, int32_t pc);
void							vs_checker(t_cw *cw, uint8_t mod);
void							vs_print_lives(t_cw *cw, uint8_t mod);

#endif
