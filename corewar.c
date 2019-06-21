#include "op_tab.h"
#include "op.h"
#include "cw.h"
#include "libft.h"

int					main()
{
	uint8_t			i;
	t_cw			cw;

	cw.num_of_champs = 2;
	cw.op_tab = cw->op;
	if (!(cw.car = (t_car*)malloc(sizeof(t_car) * cw.num_of_champs)))
		exit (ft_printf("Error\n"));
	fight(&cw);
	i = 0;
	while (i < OP_NUM)
		ft_printf("%s\n", cw->op[i++].name);
	return (0);
}

int8_t			reg_checker(t_cw *cw, uint32_t i)
{
	return (1 <= (uint32_t)cw->map[i] && (uint32_t)cw->map[i] <= REG_NUMBER);
}

/*
 * написать 3 маленькие функции по возвращению значений аргументов РЕГ, ДИР, ИНД
 * и вставить их в codage валидатор, который будет заполнять в cw: arg[3];
 * эти функции будут каутнить cw->step и возвращать true/false
 * */

int8_t			codage_validator(t_cw *cw, uint8_t op_i, uint32_t car_i)
{
	int8_t		i;
	int8_t		err;
	uint8_t		codage;
	
	i = -1;
	err = 0;
	cw->step = OPC_SIZE;
	codage = cw->map[cw->car[car_i].PC + OPCI_SIZE] >> 2;
	while (++i < OP_NUM_ARGS)
		if ((codage >> i * 2) & IND_CODE)
		{
			err -= (cw->op[op_i].args[i] & IND_CODE) ? 0 : 1;
			cw->step += IND_SIZE;
		}
		else if ((codage >> i * 2) & REG_CODE)
		{
			err -= (cw->op[op_i].args[i] & REG_CODE) ? 0 : 1;
			cw->step += REG_SIZE;
		}
		else if ((codage >> i * 2) & DIR_CODE)
		{
			err -= (cw->op[op_i].args[i] & DIR_CODE) ? 0 : 1;
			cw->step += cw->op[op_i].label_size;
		}
	cw->car[car_i].PC += (err) ? cw->step : 0;
	return (err);
}

uint32_t		arg_checker(t_cw *cw, uint8_t arg_i, uint32_t car_i)
{
	uint8_t		codage;
	uint32_t	pos;
	
	pos = cw->car[car_i].PC + OPCI_SIZE;
	codage = cw->map[pos] >> (8 - 2 * arg_i);
	if (codage & IND_CODE)
	{
		pos = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + IND_SIZE];
		err -= (cw->op[op_i].args[i] & IND_CODE) ? 0 : 1;
		cw->step += IND_SIZE;
	}
	else if ((codage >> i * 2) & REG_CODE)
	{
		err -= (cw->op[op_i].args[i] & REG_CODE) ? 0 : 1;
		cw->step += REG_SIZE;
	}
	else if ((codage >> i * 2) & DIR_CODE)
	{
		err -= (cw->op[op_i].args[i] & DIR_CODE) ? 0 : 1;
		cw->step += cw->op[op_i].label_size;
	}
	cw->car[car_i].PC += (err) ? cw->step : 0;
	return (err);
}
void			op_live(t_cw *cw, uint32_t i)
{
	uint32_t	id;

	cw->lives++;
	cw->car[i].last_live = cw->cycles;
	id = -(uint32_t)cw->map[cw->car[i].PC + OPI_SIZE + cw->op[LIVE].label_size];
	cw->car[i].PC += cw->op[LIVE].label_size + OP_SIZE;
	if (1 <= id && id <= cw->num_of_champs)
		cw->champ[id - 1].lives++;
}

void			op_ld(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;

	if (codage_validator(cw, LD, i))
		return ;
	if ((cw->map[cw->car[i].PC + OPCI_SIZE] >> 6) & IND_CODE)
	{
		pos = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + IND_SIZE];
		data = (uint32_t)cw->map[cw->car[i].PC + pos % IDX_MOD];
		pos = cw->car[i].PC + OPCI_SIZE + IND_SIZE + REG_SIZE;
	}
	else
	{
		data = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + cw->op[LD].label_size];
		pos = cw->car[i].PC + OPCI_SIZE + cw->op[LD].label_size + REG_SIZE;
	}
	if (reg_checker(cw, pos))
	{
		cw->car[i].reg[(uint32_t)cw->map[pos]] = data;
		cw->car[i].carry = (data) ? 0 : 1;
	}
	cw->car[i].PC += cw->step;
}

void			op_st(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;

	if (codage_validator(cw, ST, i))
		return ;
	if (reg_checker(cw, cw->car[i].PC + OPCI_SIZE + REG_SIZE))
	{
		if ((cw->map[cw->car[i].PC + OPCI_SIZE] >> 4) & IND_CODE)
		{
			pos = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE + IND_SIZE];
			pos = cw->car[i].PC + pos % IDX_MOD;
			(uint32_t)cw->map[pos] = cw->car[i].reg[(uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE]];
		}
		else if (reg_checker(cw, cw->car[i].PC + OPCI_SIZE + REG_SIZE * 2]))
				cw->car[i].reg[cw->car[i].PC + OPCI_SIZE + REG_SIZE * 2] =\
				   	cw->car[i].reg[(uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE]];
	}
	cw->car[i].PC += cw->step;
}

void			op_add(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;

	if (codage_validator(cw, ADD, i))
		return ;
	pos = cw->car[i].PC + OPCI_SIZE + REG_SIZE;
	cw->car[i].PC += cw->step;
	if (!(reg_checker(cw, pos) && reg_checker(cw, pos + REG_SIZE) && reg_checker(cw, pos + REG_SIZE * 2)))
		return ;
	data = cw->car[i].reg[(uint32_t)cw->map[pos]] + cw->car[i].reg[(uint32_t)cw->map[pos + REG_SIZE]];
	cw->car[i].carry = ((cw->car[i].reg[(uint32_t)cw->map[pos + REG_SIZE * 2]] = data)) ? 0 : 1;
}

void			op_sub(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;

	if (codage_validator(cw, SUB, i))
		return ;
	pos = cw->car[i].PC + OPCI_SIZE + REG_SIZE;
	cw->car[i].PC += cw->step;
	if (!(reg_checker(cw, pos) && reg_checker(cw, pos + REG_SIZE) && reg_checker(cw, pos + REG_SIZE * 2)))
		return ;
	data = cw->car[i].reg[(uint32_t)cw->map[pos]] - cw->car[i].reg[(uint32_t)cw->map[pos + REG_SIZE]];
	cw->car[i].carry = ((cw->car[i].reg[(uint32_t)cw->map[pos + REG_SIZE * 2]] = data)) ? 0 : 1;

}

void			op_and(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;
	uint32_t	size;
	uint32_t	codage;

	if (codage_validator(cw, AND, i))
		return ;
	pos = cw->car[i].PC + OPCI_SIZE;
	codage = cw->map[pos] >> 4;
	cw->car[i].PC += cw->step;
	if (codage & IND_CODE && (codage >> 2) & IND_CODE && (size = IND_SIZE))
		data = (cw->car[i].PC + (uint32_t)(map[pos + IND_SIZE] % IDX_MOD)) &\
			   (cw->car[i].PC + (uint32_t)cw->map[pos + IND_SIZE * 2] % IDX_MOD);
	else if (codage & DIR_CODE && (codage >> 2) & DIR_CODE && (size = cw->op[AND].label_size))
		data = (uint32_t)(map[pos + size]) & (uint32_t)(map[pos + size * 2]);
	else if (codage & REG_CODE && (codage >> 2) & REG_CODE && (size = REG_SIZE) &&\
			reg_checker(cw, pos + REG_SIZE) && reg_checker(cw, pos + REG_SIZE * 2))
			data = cw->car[i].reg[(uint32_t)map[pos + REG_SIZE] - 1] &\
				   cw->car[i].reg[(uint32_t)map[pos + REG_SIZE * 2] - 1];
	else
		return ;
	if (!reg_checker(cw, pos + size * 2 + REG_SIZE))
		return ;
	cw->car[i].reg[(uint32_t)cw->map[pos + size * 2 + REG_SIZE]] = data;
	cw->car[i].carry = (data) ? 0 : 1;
}

void			op_or(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;
	uint32_t	size;
	uint32_t	codage;

	if (codage_validator(cw, OR, i))
		return ;
	pos = cw->car[i].PC + OPCI_SIZE;
	codage = cw->map[pos] >> 4;
	cw->car[i].PC += cw->step;
	if (codage & IND_CODE && (codage >> 2) & IND_CODE && (size = IND_SIZE))
		data = (cw->car[i].PC + (uint32_t)(map[pos + IND_SIZE] % IDX_MOD)) |\
			   (cw->car[i].PC + (uint32_t)cw->map[pos + IND_SIZE * 2] % IDX_MOD);
	else if (codage & DIR_CODE && (codage >> 2) & DIR_CODE && (size = cw->op[OR].label_size))
		data = (uint32_t)(map[pos + size]) | (uint32_t)(map[pos + size * 2]);
	else if (codage & REG_CODE && (codage >> 2) & REG_CODE && (size = REG_SIZE) &&\
			reg_checker(cw, pos + REG_SIZE) && reg_checker(cw, pos + REG_SIZE * 2))
			data = cw->car[i].reg[(uint32_t)map[pos + REG_SIZE] - 1] |\
				   cw->car[i].reg[(uint32_t)map[pos + REG_SIZE * 2] - 1];
	else
		return ;
	if (!reg_checker(cw, pos + size * 2 + REG_SIZE))
		return ;
	cw->car[i].reg[(uint32_t)cw->map[pos + size * 2 + REG_SIZE]] = data;
	cw->car[i].carry = (data) ? 0 : 1;
}

void			op_xor(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;
	uint32_t	size;
	uint32_t	codage;

	if (codage_validator(cw, XOR, i))
		return ;
	pos = cw->car[i].PC + OPCI_SIZE;
	codage = cw->map[pos] >> 4;
	cw->car[i].PC += cw->step;
	if (codage & IND_CODE && (codage >> 2) & IND_CODE && (size = IND_SIZE))
		data = (cw->car[i].PC + (uint32_t)(map[pos + IND_SIZE] % IDX_MOD)) ^\
			   (cw->car[i].PC + (uint32_t)cw->map[pos + IND_SIZE * 2] % IDX_MOD);
	else if (codage & DIR_CODE && (codage >> 2) & DIR_CODE && (size = cw->op[XOR].label_size))
		data = (uint32_t)(map[pos + size]) ^ (uint32_t)(map[pos + size * 2]);
	else if (codage & REG_CODE && (codage >> 2) & REG_CODE && (size = REG_SIZE) &&\
			reg_checker(cw, pos + REG_SIZE) && reg_checker(cw, pos + REG_SIZE * 2))
			data = cw->car[i].reg[(uint32_t)map[pos + REG_SIZE] - 1] ^\
				   cw->car[i].reg[(uint32_t)map[pos + REG_SIZE * 2] - 1];
	else
		retun ;
	if (!reg_checker(cw, pos + size * 2 + REG_SIZE))
		return ;
	cw->car[i].reg[(uint32_t)cw->map[pos + size * 2 + REG_SIZE]] = data;
	cw->car[i].carry = (data) ? 0 : 1;
}

void			op_zjmp(t_cw *cw, uint32_t i)
{
	uint32_t	pos;

	if (!cw->car[i].carry)
		return ;
	cw->car[i].PC += (uint32_t)cw->map[cw->car[i].PC + OPI_SIZE + cw->op[ZJMP].label_size] % IDX_MOD;
}

void			op_ldi(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;
	uint32_t	codage;

	if (codage_validator(cw, LDI, i))
		return ;
	pos = cw->car[i].PC + OPCI_SIZE;
	codage = cw->map[pos] >> 4;
	cw->car[i].PC += cw->step;
	if (!reg_checker(cw, pos + size * 2 + REG_SIZE))
		return ;
	if ((cw->map[cw->car[i].PC + OPCI_SIZE] >> 6) & IND_CODE ||\
			(cw->map[cw->car[i].PC + OPCI_SIZE] >> 6) & DIR_CODE)
	{
		pos = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + IND_SIZE];
		data = (uint32_t)cw->map[cw->car[i].PC + pos % IDX_MOD] + (uint32_t)cw->car[i].PC;
		data += (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + IND_SIZE + REG_SIZE];
		pos = cw->car[i].PC + OPCI_SIZE + IND_SIZE + REG_SIZE + REG_SIZE;
	}
	else 
	{
		pos = cw->car[i].PC + OPCI_SIZE + REG_SIZE;
		data = (uint32_t)cw->map[pos + REG_SIZE] + (uint32_t)cw->map[pos];
		pos = cw->car[i].PC + OPCI_SIZE + cw->op[LD].label_size + REG_SIZE + REG_SIZE;
	}
	(uint32_t)cw->map[pos] = data % IDX_MOD;
	cw->car[i].carry = (data) ? 0 : 1;
}

static int8_t	dies_checker(t_cw *cw)
{
	cw->checks++;
	if (cw->lives >= NBR_LIVE || (cw->checks == MAX_CHECKS && cw->cycle_to_check == cw->cycle_to_die))
	{
		cw->cycle_to_die -= CYCLE_DELTA;
		cw->checks = 0;
	}
	cw->cycle_to_check = cw->cycle_to_die;
	cw->lives = 0;
	return (0);
}

static void		car_cycler(t_cw *cw)
{
	uint32_t	i;

	i = 0;
	while (i < cw->num_of_champs)
	{
		if (cw->car[i].last_live < cw->cycle_to_die)
		{
			if (!cw->car[i].cycle_to_wait)
			{
				cw->car[i].op_code = cw->map[cw->car[i].PC % MEM_SIZE];
				cw->car[i].cycle_to_wait = (1 <= cw->car[i].op_code && cw->car[i].op_code <= OP_NUM) ?
										cw->op[cw->car[i].op_code].cycles : 0;
			}
			cw->car[i].cycle_to_wait -= (cw->car[i].cycle_to_wait > 0) ? 1 : 0;
			if (!cw->car[i].cycle_to_wait)
			{
				if (1 <= cw->car[i].op_code && cw->car[i].op_code <= OP_NUM)
					cw->op[cw->car[i].op_code].f(cw, i);
				else
					cw->car[i].PC++;
			}
		}
		i++;
	}
}

int8_t				fight(t_cw *cw)
{
	cw->cycles = 0;
	cw->checks = 0;
	cw->cycle_to_die = CYCLE_TO_DIE;
	while (1)
	{
		if (cw->flg & DUMP && cw->cycles == cw->cycle_to_dump)
			exit (ft_printf("kek eto dump\n"));
		if (cw->cycle_to_die <= 0 || !(cw->cycles % cw->cycle_to_die))
			if (dies_checker(cw))
				return (1);
		car_cycler(cw);
		cw->cycles++;
	}
}
