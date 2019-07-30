#include "cw.h"
#include "libft.h"

static void		fill_head(t_cw *cw, uint8_t *head, uint8_t *exec,\
														uint8_t i_champ)
{
	int32_t		j;
	int32_t		k;

	cw->champ[i_champ]->head.magic = (head[3] & 0x000000FF) << 0 |\
						(head[2] & 0xFF) << 8 | (head[1] & 0xFF) << 16 |\
						(head[0] & 0xFF) << 24;
	if (cw->champ[i_champ]->head.magic != COREWAR_EXEC_MAGIC)
		cw_out(cw, ft_printf("%w\033[1;31mInvali_champ file type\033[0m\n", STDERR), 0);
	k = -1;
	j = MAGIC_HEADER_SIZE - 1;
	while (++j < MAGIC_HEADER_SIZE + PROG_NAME_LENGTH)
		cw->champ[i_champ]->head.prog_name[++k] = head[j];
	k = -1;
	j = MAGIC_HEADER_SIZE + PROG_NAME_LENGTH + DELIMETR_SIZE * 2 - 1;
	while (++j < HEADER_SIZE - CHAMP_EXEC_SIZE)
		cw->champ[i_champ]->head.comment[++k] = head[j];
	if (!(cw->champ[i_champ]->exec = (uint8_t*)malloc(sizeof(uint8_t) *\
									(cw->champ[i_champ]->head.prog_size + 1))))
		cw_out(cw, ft_printf("%w\033[1;31mError\033[0m\n", STDERR), 0);
	ft_memcpy(cw->champ[i_champ]->exec, exec, cw->champ[i_champ]->head.prog_size);
}

static void		fill_champ(t_cw *cw, char *file_name, uint8_t id_champ, int arg)
{
	int			fd;
	uint8_t		head[HEADER_SIZE + 1];
	uint8_t		exec[CHAMP_MAX_SIZE + 1];

	if (add_champ(cw, id_champ))
		cw_out(cw, ft_printf("%w\033[1;31mPlayer# %u is already exist ", STDERR,\
					id_champ) + ft_printf("%w[arg#: %d]\033[0m\n", STDERR, arg), 0);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		cw_out(cw, ft_printf("%w\033[1;31mFile %s error\033[0m\n", STDERR,\
																file_name), 0);
	if (read(fd, head, HEADER_SIZE) <= 0)
		cw_out(cw, ft_printf("%w\033[1;31mFile %s read error\033[0m\n", STDERR,\
																	file_name), 0);
	if ((cw->champ[IN(cw->num_of_champs)]->head.prog_size =\
									read(fd, exec, CHAMP_MAX_SIZE + 1)) <= 0)
		cw_out(cw, ft_printf("%w\033[1;31mFile %s read error\033[0m\n",\
														STDERR, file_name), 0);
	if (cw->champ[IN(cw->num_of_champs)]->head.prog_size > CHAMP_MAX_SIZE)
		cw_out(cw, ft_printf("\033[1;31mFile %s\
			has too large executable code: ", STDERR, file_name) +\
			ft_printf("%w%u > ", STDERR, cw->champ[IN(cw->num_of_champs)]->head.prog_size) +\
			ft_printf("%wCHAMP_MAX_SIZE(%u)\033[0m\n", STDERR, CHAMP_MAX_SIZE), 0);
	fill_head(cw, head, exec, IN(cw->num_of_champs));
	close(fd);
}

static int		args_analis(char *arg, char **av, t_cw *cw, int i)
{
	cw->step = 0;
	if (cw->err == DUMP)
	{
		if (!av)
			cw_out(cw, ft_printf("%w\033[1;31mInvalid dump size: %s [arg#: %d]\n",\
														STDERR, NULL, i), av[0]);
		cw->f.lag |= (arg[4]) ? DUMP64 : DUMP;
		cw->cycle_to_dump = ft_atoi(av[i]);
		if (!cw->cycle_to_dump && av[i][0] != '0')
			cw_out(cw, ft_printf("%w\033[1;31mInvalid dump size: %s [arg#: %d]\n",\
														STDERR, av[i], i), av[0]);
		return (i);
	}
	if (cw->err)
	{
		if (!av)
			cw_out(cw, ft_printf("%w\033[1;31mInvalid player number:\
							%s [arg#: %d]\n", STDERR, NULL, i), av[0]);
		if ((cw->step = ft_atoi(av[i])) < 1 || MAX_PLAYERS < cw->step)
			cw_out(cw, ft_printf("%w\033[1;31mInvalid player number:\
							%s [arg#: %d]\n", STDERR, av[i], i), av[0]);
		i++;
	}
	if (av[i] && cw_strrstr(av[i], ".cor"))
		fill_champ(cw, av[i], cw->step, i);
	else
		cw_out(cw, ft_printf("%w\033[1;31mInvalid file name: %s [arg#: %d]\n",
													STDERR, av[i], i), av[0]);
	return (i);
}

static void		flg_analis_2(char **av, t_cw *cw, int i, size_t j)
{
	if (av[i][j] == 'a' && !av[i][j + 1] && !cw->f.lg.af)
		cw->f.lag |= AF;
	else if (av[i][j] == 'd' && !av[i][j + 1] && !cw->f.lg.dbg)
		cw->f.lag |= DEBUG;
	else if (av[i][j] == 'd' && av[i][j + 1] == 'c' && !av[i][j + 2])
		cw->f.lag |= DEBUG_C;
	else if (av[i][j] == 'd' && av[i][j + 1] == 'r' && !av[i][j + 2])
		cw->f.lag |= DEBUG_R;
	else if (av[i][j] == 'd' && av[i][j + 1] == 'f' && !av[i][j + 2])
		cw->f.lag |= DEBUG_F;
	else if (av[i][j] == 'v' && !av[i][j + 1] && !cw->f.lg.vs)
		cw->f.lag |= VISU;
	else
		cw_out(cw, ft_printf("%w\033[1;31mInvalid flag: %s [arg#: %d]\n",\
											STDERR, &av[i][j], i), av[0]);	
	if (cw->f.lg.vs && cw->f.lg.dbg)
		cw_out(cw, ft_printf("%w\033[1;31mFlag 'v*' %s 'd*' [arg#: %d]\n",\
						STDERR, "do not stack with", &av[i][j], i), av[0]);
}

void			cw_flg_analis(int ac, char **av, t_cw *cw, int i)
{
	size_t		j;

	while (++i < ac)
	{
		j = 0;
		cw->err = 0;
		while (av[i][j] == ' ' || av[i][j] == '\t' || av[i][j] == '\n')
			j++;
		if (av[i][j++] != '-')
			i = args_analis(&av[i][j - 1], av, cw, i);
		else if (av[i][j] == 'n' && !av[i][j + 1] && (cw->err = 0xff))
			i = args_analis(&av[i][j], ((i + 1 < ac) ? av : NULL), cw, i + 1);
		else if ((!ft_strcmp(&av[i][j], "dump") ||\
		!ft_strcmp(&av[i][j], "dump64")) && !cw->f.lg.dump && (cw->err = DUMP))
			i = args_analis(&av[i][j], ((i + 1 < ac) ? av : NULL), cw, i + 1);
		else if (av[i][j] == 's' && !av[i][j + 1])
		{
			cw->f.lag |= PRG_STRT;
			if (++i == ac || (!(cw->start_cycle = ft_atoi(av[i])) && av[i][0] != '0'))
				cw_out(cw, ft_printf("%w\033[1;31mInvalid cycle value: %s [arg#: %d]\n",\
											STDERR, (i == ac) ? NULL : av[i], i), av[0]);
		}
		else
			flg_analis_2(av, cw, i, j);
	}
}
