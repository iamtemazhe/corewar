#include "op_tab.h"
#include "op.h"
#include "cw.h"
#include "libft.h"

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
	uint8_t		i_car;

	i_car = 0;
	while (i_car < cw->num_of_cars)
	{
		if (cw->car[i_car]->last_live < cw->cycle_to_die)
		{
			if (!cw->car[i_car]->cycle_to_wait)
			{
				cw->car[i_car]->op_code = cw->map[cw->car[i_car]->pc % MEM_SIZE];
				cw->car[i_car]->cycle_to_wait =\
					(1 <= cw->car[i_car]->op_code && cw->car[i_car]->op_code <= OP_NUM) ?\
												cw->op[cw->car[i_car]->op_code].cycles : 0;
			}
			if (!(cw->car[i_car]->cycle_to_wait = IN(cw->car[i_car]->cycle_to_wait)))
			{
				if (1 <= cw->car[i_car]->op_code && cw->car[i_car]->op_code <= OP_NUM)
				{
					ft_printf("op_code = %ud\n", cw->car[i_car]->op_code);
					cw->op[cw->car[i_car]->op_code].f(cw, i_car);
				}
				else
					cw->car[i_car]->pc = ++cw->car[i_car]->pc % MEM_SIZE;
			}
		}
		i_car++;
	}
}

void				fight(t_cw *cw)
{
	while (1)
	{
		ft_printf("%d\n", cw->cycles);
		ft_printf("num_of_champs = %d\n", cw->num_of_champs);
		ft_printf("cw->cycle_to_die = %d\n", cw->cycle_to_die);
		if (cw->flg & DUMP && cw->cycles == cw->cycle_to_dump)
			exit (ft_printf("kek eto dump\n"));
		ft_printf("cw->cycle_to_die = %d\n", cw->cycle_to_die);
		if (cw->cycle_to_die <= 0 || (cw->cycles && !(cw->cycles % cw->cycle_to_die)))
			if (dies_checker(cw))
				return ;
		ft_printf("cw->cycle_to_die = %d\n", cw->cycle_to_die);
		car_cycler(cw);
		cw->cycles++;
		ft_printf("cw->cycle_to_die = %d\n", cw->cycle_to_die);
		// visu(cw);
	}
}

int					main(int ac, char **av)
{
	t_cw			cw;
	uint			j;

	init_cw(&cw);
	j = 0;
	fill_cw(ac, av, &cw);
	ft_printf("num_of_champs = %d\n", cw.num_of_champs);
	ft_printf("cw->cycle_to_dump = %d\n", cw.cycle_to_dump);
	while (j < cw.num_of_champs)
	{
		ft_printf("name_%d = %s\n", j, cw.champ[j].head.prog_name);
		ft_printf("size = %ud\n", j, cw.champ[j].head.prog_size);
		ft_printf("comment = %s\n", cw.champ[j].head.comment);
		ft_printf("id = %d\n", cw.champ[j].id);
		j++;
	}
	j = 0;
	while (j < 4096)
	{
		ft_printf("%x",  cw.map[j]);
		j++;
	}
	// init_visu(&cw);
	// visu(&cw);
	add_car(&cw, 0);
	fight(&cw);
	return (0);
}
