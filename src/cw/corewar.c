#include "cw.h"
#include "libft.h"

static int8_t	dies_checker(t_cw *cw)
{
	size_t		i;

	// ft_printf("checks = %d, lives = %d, cycle = %u, die = %d\n\r", cw->checks, cw->lives, cw->cycles, cw->cycle_to_die);
	i = cw->num_of_cars;
	if (cw->f.lg.vs)
		vs_print_lives(cw, 1);
	while (--i > 0)
		if ((int32_t)(cw->cycles - cw->car[i]->last_live) >= cw->cycle_to_die)
			del_car(cw, i);
	if (++cw->checks == MAX_CHECKS || cw->lives >= NBR_LIVE)
	{
		cw->cycle_to_die -= CYCLE_DELTA;
		cw->checks = 0;
		if (cw->f.lg.vs)
			vs_checker(cw, 1);
	}
	cw->lives = 0;
	while (++i < cw->num_of_champs)
		cw->champ[i]->lives = 0;
	if (cw->f.lg.vs)
		vs_checker(cw, 0);
	return ((cw->num_of_cars) ? 0 : -1);
}

static void		car_cycler(t_cw *cw)
{
	size_t		i_car;
	int8_t		show;

	show = 1;
	cw->f.lg.vs_live = 0;
	i_car = cw->num_of_cars;
	while (i_car-- > 0)
	{
		if (!cw->car[i_car]->cycle_to_wait)
		{
			cw->car[i_car]->op_code = cw->map[cw->car[i_car]->pc].v.code;
			if (cw->car[i_car]->op_code < 1 || OP_NUM < cw->car[i_car]->op_code)
			{
				if (cw->f.lg.vs)
					vs_backlight_car(cw, i_car, 1, 1);
				cw->car[i_car]->pc = (cw->car[i_car]->pc + 1) % MEM_SIZE;
				continue ;
			}
			cw->car[i_car]->cycle_to_wait = cw->op[IN(cw->car[i_car]->op_code)].cycles;
		}
		if (cw->f.lg.dbg_c && show && cw->car[i_car]->cycle_to_wait == 1)
		{
			show = 0;
			ft_printf("%38\033[37m|\033[1m%9d  Cycle: %7zu%9\033[22m|\n\r", cw->cycles);
		}
		if (!(cw->car[i_car]->cycle_to_wait = IN(cw->car[i_car]->cycle_to_wait)))
			cw->op[IN(cw->car[i_car]->op_code)].f(cw, i_car);
	}
}

void				fight(t_cw *cw)
{
	while (1)
	{
		if (cw->f.lg.vs)
			vs(cw);
		if (cw->f.lg.dump && cw->cycles == cw->cycle_to_dump)
			dump(cw);
		if (cw->cycle_to_die <= 0 || !(cw->cycles % cw->cycle_to_die))
			if (dies_checker(cw))
				return ;
		car_cycler(cw);
		cw->cycles++;
	}
}

int					main(int ac, char **av)
{
	t_cw			cw;

	init_cw(&cw);
	fill_cw(ac, av, &cw);
	if (cw.f.lg.vs)
		vs_init(&cw);
	if (cw.f.lg.dbg)
		dbg_log_top();
	add_car(&cw, 0, 0);
	if (!cw.f.lg.vs)
	{
		ft_printf("Introducing contestants...\n");
		int i = -1;
		while (++i < cw.num_of_champs)
			ft_printf("* Player %u, weighing %u bytes, \"%s\" (\"%s\") !\n",\
								cw.champ[i]->id, cw.champ[i]->head.prog_size,\
						cw.champ[i]->head.prog_name, cw.champ[i]->head.comment);
	}
	fight(&cw);
	if (cw.f.lg.dbg)
		dbg_log_bot();
	// int j = 0;
	// while (j < 4096)
	// {
	// 	ft_printf("%x",  cw.map[j].v.code);
	// 	j++;
	// }
	// int32_t	i = -5000;
	// while (i < 5000)
	// {
	// 	ft_printf("%u ", PCV(i));
	// 	i++;
	// }
	// ft_printf("\n\rcycles = %u\n", cw.cycles);
	if (cw.f.lg.vs)
	{
		while (wgetch(cw.vs.menu) == ERR)
			sleep(1);
		endwin();
	}
	return (0);
}
