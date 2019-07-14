#include "cw.h"

static void			reg(t_cw *cw, uint8_t i_arg, uint8_t i_car, uint8_t i_op)
{
	cw->step += REGN_SIZE;
	if (!(cw->op[i_op].args[i_arg] & T_REG))
		cw->err = -1;
	if (cw->err)
		return ;
	cw->pos = cw->car[i_car]->pc + cw->step;
	cw->arg_code[i_arg] = cw->map[PC(cw->pos)];
	if (1 <= cw->arg_code[i_arg] && cw->arg_code[i_arg] <= REG_NUMBER)
		cw->arg[i_arg] = cw->arg_code[i_arg];
	else
		cw->err = -1;
}

static void			ind(t_cw *cw, uint8_t i_arg, uint8_t i_car, uint8_t i_op)
{
	cw->step += IND_SIZE;
	if (!(cw->op[i_op].args[i_arg] & T_IND))
		cw->err = -1;
	if (cw->err)
		return ;
	cw->pos = cw->car[i_car]->pc + cw->step;
	cw->arg_code[i_arg] = code_to_byte(cw->map, cw->pos, IND_SIZE);
	cw->arg[i_arg] = (int16_t)cw->arg_code[i_arg] % IDX_MOD + cw->car[i_car]->pc;
}

static void		dir(t_cw *cw, uint8_t i_arg, uint8_t i_car, uint8_t i_op)
{
	cw->step += cw->op[i_op].label_size;
	if (!(cw->op[i_op].args[i_arg] & T_DIR))
		cw->err = -1;
	if (cw->err)
		return ;
	cw->pos = cw->car[i_car]->pc + cw->step;
	cw->arg_code[i_arg] = code_to_byte(cw->map, cw->pos, cw->op[i_op].label_size);
	cw->arg[i_arg] = cw->pos;
}

int8_t			codage_validator(t_cw *cw, uint8_t i_car, uint8_t i_op)
{
	int8_t		i_arg;
	uint8_t		code;

	cw->step = OPC_SIZE;
	ft_bzero(cw->arg, sizeof(*cw->arg) * OP_NUM_ARGS);
	ft_bzero(cw->arg_code, sizeof(*cw->arg_code) * OP_NUM_ARGS);
	cw->cod.age = cw->map[PC(cw->car[i_car]->pc + cw->step)];
	cw->err = (cw->cod.arg.v4) ? -1 : 0;
	i_arg = -1;
	while (++i_arg < cw->op[i_op].num_args)
		if ((code = (cw->cod.age >> (6 - i_arg * 2)) & 0x3) && code == IND_CODE)
			ind(cw, i_arg, i_car, i_op);
		else if (code == REG_CODE)
			reg(cw, i_arg, i_car, i_op);
		else if (code == DIR_CODE)
			dir(cw, i_arg, i_car, i_op);
		else
			cw->err = -1;
	if (cw->flg & DEBUG)
		dbg_log_cod(cw, i_car);
	if (!cw->err)
		return (0);
	cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + cw->step);
	cw->cod.age = 0;
	cw->err = 0;
	return (-1);
}