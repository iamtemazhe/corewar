int					main()
{
	char			i;
	char			j;
	t_car			*car;

	if (!(car = (t_car*)malloc(t_car * n_champs)))
		exit ("Error\n");
	while(live_process > 0 && cycle_to_die > 0)
	{
		i = -1;
		while (++i < n_champs)
		{
			j = -1;
			while (g_op_tab[j].command)
				if (car->command == g_op_tab[j].command)
				{
					g_op_tab[j].f(&car[i]);
					break ;
				}
		}
	}
}

void			op_live(t_cw *cw, t_car *car)
{
	int32_t		id;

	cw->lives++;
	car->last_live = cw->cycles;
	id = (int32_t)vm->map[car->pos + g_op[0].label_size];
	car->pos += g_op[0].label_size + OP_CODE;
	if (-(int32_t)cw->num_champs <= id && id <= -1)
		car->champ.state = 1;
}

void				op_ld(t_car *car, unsigned char **map)
{
	unsigned char	args;
	unsigned int	pos;

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
				if (!car[i]->wait_cycles && 1 <= car[i]->op_code && car[i]->op_code && <= OP_NUM)

int				fight()
{
	cw->cycles = -1;
	cw->checks = 0;
	cw->cycles_to_die <= CYCLES_TO_DIE;
	while (++cw->cycles)
	{
		if (cw->flg & DUMP && cw->cycles == cw->cycles_dump)
			exit (ft_printf("kek eto dump\n"));
		if (cw->cycles_to_die <= 0 || !(cw->cycles % cw->cycles_to_die))
		{
			cw->checks++;
			if (cw->lives >= NBR_LIVE || (cw->checks == MAX_CHECKS && cw->cycles_check == cw->cycles_to_die))
			{
				cw->cycles_to_die -= CYCLE_DELTA;
				cw->checks = 0;
			}
			cw->cycles_check = cw->cycles_to_die;
			cw->lives = 0;
		}
		i = -1;
		while (++i < n_champs)
			if (cw->car[i].last_live < cw->cycles_to_die)
			{
				if (!cw->car[i].wait_cycles)
				{
					car[i]->op_code = cw->map[car[i]->pos % MEM_SIZE];
					car[i]->wait_cycles = (1 <= car[i]->op_code && car[i]->op_code && <= OP_NUM) ?
											g_op_tab[j].cycles : 0;
				}
				car[i]->wait_cycles -= (car[i]->wait_cycles > 0) ? 1 : 0;
				if (!car[i]->wait_cycles)
				{
					if (1 <= car[i]->op_code && car[i]->op_code && <= OP_NUM)
						g_op_tab[j].f(&cw, &car[i]);
					else
						car[i]->pos++;
				}
			}
	}
}
