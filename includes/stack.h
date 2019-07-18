#ifndef STACK_H
# define STACK_H

# include <stdlib.h>
# include <stdint.h>

typedef struct					s_stack
{
	uint8_t						n;
	uint32_t					pc;
	uint32_t					cycle_to_show;
	struct s_stack				*prev;
	struct s_stack				*next;
}								t_stack;

void							st_del(t_stack **st_p);
int8_t							st_err(int8_t retv, t_stack **st_p);
t_stack							*st_new(size_t arg, size_t n);
t_stack							*st_add(size_t arg, t_stack *st_dst);

#endif
