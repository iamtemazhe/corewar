# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 13:26:35 by jwinthei          #+#    #+#              #
#    Updated: 2019/06/14 18:53:22 by jwinthei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CORE = corewar
VISU = visu_hex
LIBN = libft.a
MLXN = mlx.a

OP_D = operations
OP_S = op_live.c op_ld.c op_st.c
SRC  =
SRC1 = $(SRC) $(addprefix $(OP_D)/, $(OP_C))
SRC2 = visu.c   $(SRC) inp_keyboard.c inp_mouse.c inp_params.c img_params.c put_image.c	\
	   draw_line.c draw_circle.c ant.c room.c

INCL = libft/includes/
LIB  = libft/
MLX  = minilibx_macos/

FLG  = -Wall -Wextra -Werror
FRAEM= -framework OpenGL -framework AppKit
CFLAGS=-O3 -I $(INCL) -I $(MLX) $(FLG) 

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

all: $(LIBN) $(CORE)


$(LIBN): $(LIB)*.c
	@make -C $(LIB)

$(MLXN): $(MLX)*.c
	@make -C $(MLX)

$(CORE): $(LIB)*.c $(OBJ1)
	gcc -O2 -o $(CORE) $(OBJ1) $(CFLAGS) -L $(LIB) -lft




$(VISU): $(LIB)*.c $(MLX)*.c $(OBJ2)
	gcc -O2 -o $(VISU) $(OBJ2) $(CFALGS) -L $(LIB) -lft -L $(MLX) -lmlx $(FRAEM)

clean:
	rm -f *.o
	make -C $(LIB) clean

fclean: clean
	rm -f $(CORE)
	make -C $(LIB) fclean

re: fclean all
