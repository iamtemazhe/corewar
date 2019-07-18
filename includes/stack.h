#ifndef STACK_H
# define STACK_H

# include "cw.h"
# include <stdlib.h>
# include <stdint.h>

typedef struct					s_stack
{
	uint8_t						n;
	uint8_t						id;
	uint8_t						op_code;
	uint32_t					pc;
	size_t						cycle_to_show;
	struct s_stack				*prev;
	struct s_stack				*next;
}								t_stack;

#endif
