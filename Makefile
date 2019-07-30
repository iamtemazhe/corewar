# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 13:26:35 by jwinthei          #+#    #+#              #
#    Updated: 2019/07/30 16:22:35 by jwinthei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CW   = corewar
VS   = vs_hex
LIB  = libft.a

SRC_D= src/
CW_D = cw/
ASM_D= asm/
OP_D = op/
VS_D = vs/
LIB_D= libft/

INC_S= includes/
INC_L= libft/includes/

OP_S =	op_add.c	op_aff.c	op_and.c	op_fork.c	op_ld.c		op_ldi.c\
		op_lfork.c	op_live.c	op_lld.c	op_lldi.c	op_or.c		op_st.c\
		op_sti.c	op_sub.c	op_xor.c	op_zjmp.c

VS_S =	vs.c			vs_init.c	vs_func.c	vs_print_windows.c

CW_S =	corewar.c		cw_init.c	cw_out.c	cw_strrstr.c\
		champ_func.c	car_func.c	dbg_log.c	cw_byte_func.c\
		cw_map_filler.c	cw_validator.c			cw_codage_validator.c


CW_C =	$(addprefix $(SRC_D)/$(CW_D), $(CW_S))	$(addprefix $(SRC_D)/$(CW_D)/$(OP_D)/, $(OP_S))\
		$(addprefix $(SRC_D)/$(VS_D), $(VS_S))

FLG  = -Wall -Wextra -Werror
CFLAGS=-O2 -I $(INC_L) -I $(INC_S) $(FLG) 

CW_O = $(CW_C:.c=.o)

all: $(LIB) $(CW)

$(LIB): $(LIB_D)*.c
	@make -C $(LIB_D)

$(CW): $(LIB_D)*.c $(CW_O)
	gcc -O2 -o $(CW) $(CW_O) $(CFLAGS) -L $(LIB_D) -lft -lncurses

clean:
	rm -f *.o
	rm -f $(SRC_D)/$(VS_D)/*.o
	rm -f $(SRC_D)/$(CW_D)/*.o
	rm -f $(SRC_D)/$(CW_D)/$(OP_D)/*.o
	make -C $(LIB_D) clean

fclean: clean
	rm -f $(CW)
	make -C $(LIB_D) fclean

re: fclean all
