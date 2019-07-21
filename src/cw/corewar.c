#include "cw.h"
#include "libft.h"

static int8_t	dies_checker(t_cw *cw)
{
	size_t		i_car;

	i_car = 0;
	// vs_checker(cw);
	while (i_car < cw->num_of_cars)
	{
		if ((int32_t)(cw->cycles - cw->car[i_car]->last_live) >= cw->cycle_to_die)
			del_car(cw, i_car);
		i_car++;
	}
	if (++cw->checks == MAX_CHECKS || cw->lives >= NBR_LIVE)
	{
		cw->cycle_to_die -= CYCLE_DELTA;
		cw->checks = 0;
	}
	cw->lives = 0;
	return ((cw->num_of_cars) ? 0 : -1);
}

static void		car_cycler(t_cw *cw)
{
	size_t	i_car;

	i_car = cw->num_of_cars;
	while (i_car-- > 0)
	{
		if (!cw->car[i_car]->cycle_to_wait)
		{
			cw->car[i_car]->op_code = cw->map[cw->car[i_car]->pc];
			if (cw->car[i_car]->op_code < 1 || OP_NUM < cw->car[i_car]->op_code)
			{
				cw->car[i_car]->pc = PCV(cw->car[i_car]->pc + 1);
				// if (cw->f.lg.vs)
					// vs_backlight_car(cw, i_car, 1);
				i_car++;
				continue ;
			}
			cw->car[i_car]->cycle_to_wait = cw->op[IN(cw->car[i_car]->op_code)].cycles;
		}
		if (!(cw->car[i_car]->cycle_to_wait = IN(cw->car[i_car]->cycle_to_wait)))
			cw->op[IN(cw->car[i_car]->op_code)].f(cw, i_car);
	}
}

void				fight(t_cw *cw)
{
	while (1)
	{
		if (cw->f.lg.dbg_c)
			ft_printf("%38\033[37m|\033[1m%8s  Cycle: %7zu%9\033[22m|\n\r", "", cw->cycles);
		if (cw->f.lg.dump && cw->cycles == cw->cycle_to_dump)
			dump(cw);
		if (cw->cycle_to_die <= 0 || (cw->cycles && !(cw->cycles % cw->cycle_to_die)))
			if (dies_checker(cw))
				return ;
		car_cycler(cw);
		cw->cycles++;
		if (cw->f.lg.vs)
			visu(cw);
		write(0, 0, 0);
	}
}

int					main(int ac, char **av)
{
	t_cw			cw;

	init_cw(&cw);
	fill_cw(ac, av, &cw);
	// ft_printf("num_of_champs = %d\n\r", cw.num_of_champs);
	// ft_printf("cw->cycle_to_dump = %d\n\r", cw.cycle_to_dump);
	// j = 0;
	// while (j < cw.num_of_champs)
	// {
	// 	ft_printf("name_%d = %s\n\r", j, cw.champ[j].head.prog_name);
	// 	ft_printf("size = %ud\n\r", j, cw.champ[j].head.prog_size);
	// 	ft_printf("comment = %s\n\r", cw.champ[j].head.comment);
	// 	ft_printf("id = %d\n\r", cw.champ[j].id);
	// 	j++;
	// }
	// j = 0;
	// while (j < 4096)
	// {
	// 	ft_printf("%x",  cw.map[j]);
	// 	j++;
	// }
	// ft_printf("\n\r");
	if (cw.f.lg.vs)
		init_visu(&cw);
	if (cw.f.lg.dbg)
		dbg_log_top();
	add_car(&cw, 0);
	fight(&cw);
	if (cw.f.lg.dbg)
		dbg_log_bot();
	// int j = 0;
	// while (j < 4096)
	// {
	// 	ft_printf("%x",  cw.map[j]);
	// 	j++;
	// }
	// int32_t	i = -5000;
	// while (i < 5000)
	// {
	// 	ft_printf("%u ", PCV(i));
	// 	i++;
	// }
	ft_printf("\n\rcycles = %u\n", cw.cycles);
	if (cw.f.lg.vs)
	{
		while (wgetch(cw.visu.menu) != 'q')
			sleep(1);
		endwin();
	}
	return (0);
}
