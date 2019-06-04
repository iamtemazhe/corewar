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

void			live(t_car *car, unsigned char **map)
{
	car->state = 1;
	if (car->champ.id == (unsigned int)map[0][car->pos + car->label_size])
		car->champ.state = 1;
}

void				ld(t_car *car, unsigned char **map)
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
