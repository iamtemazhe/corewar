#include "op.h"
#include "cw.h"
#include "libft.h"

int					main()
{
	unsigned char	i;
	t_car			*car;
	t_cw			cw;

	cw.num_of_champs = 2;
	if (!(car = (t_car*)malloc(sizeof(t_car) * cw.num_of_champs)))
		exit (ft_printf("Error\n"));
//	fight(&cw);
	i = 0;
	while (i < 3)
		ft_printf("%s\n", g_op[i++].name);
	return (0);
}

void			op_live(t_cw *cw, t_car *car)
{
	uint32_t		id;

	cw->lives++;
	car->last_live = cw->cycles;
	id = -(uint32_t)cw->map[car->PC + g_op[0].label_size];
	car->PC += g_op[0].label_size + OP_CODE;
	if (1 <= id && id <= cw->num_of_champs)
		cw->champ[id - 1].lives++;
}
/*
void			op_ld(t_car *car, unsigned char **map)
{
	uint32_t	pos;

	pos = car->pos + car->codage;
	args = (unsigned char)map[0][pos] >> 4;
	if (!(args & T_REG))
		return ;
	if (args & T_DIR && (pos = map[0][car->pos + car->label_size + 1]) < 17)
		car->reg[pos] = (unsigned int)map[0][car->pos + car->label_size];
	else if (args & T_IND)

	   	&& (pos = map[0][car->pos + car->label_size + 1]) < 17)
		car->champ.state = 1;
}
*/
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
										g_op[cw->car[i].op_code].cycles : 0;
			}
			cw->car[i].cycle_to_wait -= (cw->car[i].cycle_to_wait > 0) ? 1 : 0;
			if (!cw->car[i].cycle_to_wait)
			{
				if (1 <= cw->car[i].op_code && cw->car[i].op_code <= OP_NUM)
					g_op[cw->car[i].op_code].f(cw, &cw->car[i]);
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
