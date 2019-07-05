#include "cw.h"

static void			reg(t_cw *cw, uint8_t i_arg, uint8_t i_car)
{
	cw->step += REG_SIZE;
	if (cw->err)
		return ;
	cw->pos = cw->car[i_car]->pc + cw->step;
	if (1 <= cw->map[PC(cw->pos)] && cw->map[PC(cw->pos)] <= REG_NUMBER)
		cw->arg[i_arg] = cw->map[PC(cw->pos)] - 1;
	else
		cw->err = -1;
}

static void			ind(t_cw *cw, uint8_t i_arg, uint8_t i_car)
{
	cw->step += IND_SIZE;
	if (cw->err)
		return ;
	cw->pos = cw->car[i_car]->pc + cw->step;
	cw->arg[i_arg] = code_to_byte(cw->map, cw->pos, REG_SIZE) % IDX_MOD + cw->car[i_car]->pc;
}

static void		dir(t_cw *cw, uint8_t i_arg, uint8_t i_car, uint8_t i_op)
{
	cw->step += cw->op[i_op].label_size;
	if (cw->err)
		return ;
	cw->arg[i_arg] = cw->car[i_car]->pc + cw->step;
}

int8_t			codage_validator(t_cw *cw, uint8_t i_car, uint8_t i_op)
{
	int8_t		i_arg;

	cw->err = 0;
	cw->step = OPC_SIZE;
	cw->cod.age = cw->map[PC(cw->car[i_car]->pc + cw->step)];
	if (!(cw->cod.arg.v1 & cw->op[i_op].args[0] &&\
			cw->cod.arg.v2 & cw->op[i_op].args[1] &&\
			cw->cod.arg.v3 & cw->op[i_op].args[2]) || cw->cod.arg.v4)
		cw->err = -1;
	i_arg = -1;
	while (++i_arg < cw->op[i_op].num_args)
		if ((cw->cod.age >> (8 - i_arg * 2)) & IND_CODE)
			ind(cw, i_arg, i_car);
		else if ((cw->cod.age >> (8 - i_arg * 2)) & REG_CODE)
			reg(cw, i_arg, i_car);
		else
			dir(cw, i_arg, i_car, i_op);
	if (!cw->err)
		return (0);
	cw->car[i_car]->pc += cw->step;
	cw->err = 0;
	return (-1);
}