#include "op_tab.h"
#include "op.h"
#include "cw.h"
#include "libft.h"

void				add_car(t_cw *cw, uint8_t i_car)
{
	if (!cw->car)
	{
		cw->num_of_cars = cw->num_of_champs;
		if (!(cw->car = (t_car *)malloc(sizeof(t_car) * cw->num_of_cars)))
			exit (ft_printf("Error\n"));
		return ;
	}
	cw->num_of_cars++;
	if (!(cw->car = (t_car *)realloc(cw->car, sizeof(t_car) * cw->num_of_cars)))
		exit (ft_printf("Error\n"));
	cw->car[cw->num_of_cars - 1].id = cw->num_of_cars;
	cw->car[cw->num_of_cars - 1].carry = cw->car[i_car].carry;
	cw->car[cw->num_of_cars - 1].last_live = cw->car[i_car].last_live;
	ft_memcpy(cw->car[cw->num_of_cars - 1].reg, cw->car[i_car].reg, REG_NUMBER * sizeof(int32_t));
}

int					main()
{
	uint8_t			i;
	t_cw			cw;

	cw.num_of_champs = 2;
	cw.op = g_op;
	add_car(&cw, 0);
	fight(&cw);
	i = 0;
	while (i < OP_NUM)
		ft_printf("%s\n", cw.op[i++].name);
	return (0);
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
	while (i < cw->num_of_cars)
	{
		if (cw->car[i].last_live < cw->cycle_to_die)
		{
			if (!cw->car[i].cycle_to_wait)
			{
				cw->car[i].op_code = cw->map[cw->car[i].pc % MEM_SIZE];
				cw->car[i].cycle_to_wait = (1 <= cw->car[i].op_code && cw->car[i].op_code <= OP_NUM) ?\
										cw->op[cw->car[i].op_code].cycles : 0;
			}
			cw->car[i].cycle_to_wait -= (cw->car[i].cycle_to_wait > 0) ? 1 : 0;
			if (!cw->car[i].cycle_to_wait)
			{
				if (1 <= cw->car[i].op_code && cw->car[i].op_code <= OP_NUM)
					cw->op[cw->car[i].op_code].f(cw, i);
				else
					cw->car[i].pc++;
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
