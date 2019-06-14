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

int8_t			codage_validator(t_cw *cw, uint8_t op_i, uint32_t car_i)
{
	int8_t		i;
	int8_t		err;
	uint8_t		codage;
	
	i = -1;
	err = 0;
	cw->step = CODAGE_SIZE + OP_SIZE;
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
	(uint32_t)cw->map[pos] = data;
	cw->car[i].carry = (data) ? 0 : 1;
	cw->car[i].PC += cw->step;
}

void			op_st(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;

	if (codage_validator(cw, ST, i))
		return ;
	if ((cw->map[cw->car[i].PC + OPCI_SIZE] >> 4) & IND_CODE)
	{
		pos = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE + IND_SIZE];
		pos = cw->car[i].PC + pos % IDX_MOD;
		(uint32_t)cw->map[pos] = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE];
	}
	else
	{
		data = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE + REG_SIZE];
		if (1 <= data && data <= REG_NUMBER)
			cw->car[i].reg[data - 1] = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE];
	}
	cw->car[i].PC += cw->step;
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
