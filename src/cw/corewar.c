#include "cw.h"
#include "libft.h"

static int8_t	dies_checker(t_cw *cw)
{
	uint8_t		i_car;

	i_car = 0;
	while (i_car < cw->num_of_cars)
	{
		if (cw->car[i_car]->last_live >= cw->cycle_to_die)
			del_car(cw, i_car);
		i_car++;
	}
	cw->checks++;
	if (cw->lives >= NBR_LIVE || (cw->checks == MAX_CHECKS && cw->cycle_to_check == cw->cycle_to_die))
	{
		cw->cycle_to_die -= CYCLE_DELTA;
		cw->checks = 0;
	}
	cw->cycle_to_check = cw->cycle_to_die;
	cw->lives = 0;
	if (cw->num_of_cars <= 0)
		return (-1);
	return (0);
}

static void		car_cycler(t_cw *cw)
{
	uint8_t		i_car;

	i_car = 0;
	while (i_car < cw->num_of_cars)
	{
		if (!cw->car[i_car]->cycle_to_wait)
		{
			cw->car[i_car]->op_code = cw->map[cw->car[i_car]->pc];
			if (!(1 <= cw->car[i_car]->op_code && cw->car[i_car]->op_code <= OP_NUM))
			{
				cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + 1);
				i_car++;
				continue ;
			}
			// ft_printf(" op_code[%u] = %u ", i_car, cw->car[i_car]->op_code);
			cw->car[i_car]->cycle_to_wait = cw->op[IN(cw->car[i_car]->op_code)].cycles;
		}
		if (!(cw->car[i_car]->cycle_to_wait = IN(cw->car[i_car]->cycle_to_wait)))
			cw->op[IN(cw->car[i_car]->op_code)].f(cw, i_car);
		i_car++;
	}
}

void				fight(t_cw *cw)
{
	while (1)
	{
		// ft_printf("%d\n", cw->cycles);
		// ft_printf("num_of_champs = %d\n", cw->num_of_champs);
		// ft_printf("cw->cycle_to_die = %d\n", cw->cycle_to_die);
		if (cw->flg & DUMP && cw->cycles == cw->cycle_to_dump)
			exit (ft_printf("kek eto dump\n"));
		if (cw->cycle_to_die <= 0 || (cw->cycles && !(cw->cycles % cw->cycle_to_die)))
			if (dies_checker(cw))
				return ;
		car_cycler(cw);
		cw->cycles++;
		// ft_printf("%u ", cw->cycles);
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
	cw.flg |= DEBUG;
	ft_printf("num_of_champs = %d\n\r", cw.num_of_champs);
	ft_printf("cw->cycle_to_dump = %d\n\r", cw.cycle_to_dump);
	while (j < cw.num_of_champs)
	{
		ft_printf("name_%d = %s\n\r", j, cw.champ[j].head.prog_name);
		ft_printf("size = %ud\n\r", j, cw.champ[j].head.prog_size);
		ft_printf("comment = %s\n\r", cw.champ[j].head.comment);
		ft_printf("id = %d\n\r", cw.champ[j].id);
		j++;
	}
	j = 0;
	while (j < 4096)
	{
		ft_printf("%x",  cw.map[j]);
		j++;
	}
	ft_printf("\n\r");
	// init_visu(&cw);
	// visu(&cw);
	add_car(&cw, 0);
	if (cw.flg & DEBUG)
		dbg_log_top();
	fight(&cw);
	if (cw.flg & DEBUG)
		dbg_log_bot();
	j = 0;
	while (j < 4096)
	{
		ft_printf("%x",  cw.map[j]);
		j++;
	}
	ft_printf("\n\rcycles = %u\n", cw.cycles);
	// j = 0;
	// while (++j < 100)
		// select_key(&cw);
	// endwin();
	return (0);
}
