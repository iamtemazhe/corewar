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
		exit(ft_printf("%w\033[1;31mInvali_champ file type\033[0m\n", STDERR));
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
		exit(ft_printf("%w\033[1;31mError\033[0m\n", STDERR));
	ft_memcpy(cw->champ[i_champ]->exec, exec, cw->champ[i_champ]->head.prog_size);
}

static void		fill_champ(t_cw *cw, char *file_name, uint8_t id_champ, int arg)
{
	int			fd;
	uint8_t		head[HEADER_SIZE + 1];
	uint8_t		exec[CHAMP_MAX_SIZE + 1];

	if (add_champ(cw, id_champ))
		exit(ft_printf("%w\033[1;31mPlayer# %u is already exist ", STDERR,\
				id_champ) + ft_printf("%w[arg#: %d]\033[0m\n", STDERR, arg));
	if ((fd = open(file_name, O_RDONLY)) < 0)
		exit(ft_printf("%w\033[1;31mFile %s error\033[0m\n", STDERR,\
																file_name));
	if (read(fd, head, HEADER_SIZE) <= 0)
		exit(ft_printf("%w\033[1;31mFile %s read error\033[0m\n", STDERR,\
																file_name));
	if ((cw->champ[IN(cw->num_of_champs)]->head.prog_size =\
									read(fd, exec, CHAMP_MAX_SIZE + 1)) <= 0)
		exit(ft_printf("%w\033[1;31mFile %s read error\033[0m\n",\
														STDERR, file_name));
	if (cw->champ[IN(cw->num_of_champs)]->head.prog_size > CHAMP_MAX_SIZE)
		exit(ft_printf("\033[1;31mFile %s\
			has too large executable code: ", STDERR, file_name) +\
			ft_printf("%w%u > ", STDERR, cw->champ[IN(cw->num_of_champs)]->head.prog_size) +\
			ft_printf("%wCHAMP_MAX_SIZE(%u)\033[0m\n", STDERR, CHAMP_MAX_SIZE));
	fill_head(cw, head, exec, IN(cw->num_of_champs));
	close(fd);
}

static int		args_analis(char *arg, char **av, t_cw *cw, int i)
{
	cw->step = 0;
	if (cw->err == DUMP)
	{
		if (!av)
			usage(ft_printf("%w\033[1;31mInvalid dump size: %s [arg#: %d]\n",\
												STDERR, NULL, i), av[0]);
		cw->f.lag |= (arg[4]) ? DUMP64 : DUMP;
		cw->cycle_to_dump = ft_atoi(av[i]);
		if (!cw->cycle_to_dump && av[i][0] != '0')
			usage(ft_printf("%w\033[1;31mInvalid dump size: %s [arg#: %d]\n",\
												STDERR, av[i], i), av[0]);
		return (i);
	}
	if (cw->err)
	{
		if (!av)
			usage(ft_printf("%w\033[1;31mInvalid player number:\
							%s [arg#: %d]\n", STDERR, NULL, i), av[0]);
		if ((cw->step = ft_atoi(av[i])) < 1 || MAX_PLAYERS < cw->step)
			usage(ft_printf("%w\033[1;31mInvalid player number:\
							%s [arg#: %d]\n", STDERR, av[i], i), av[0]);
		i++;
	}
	if (av[i] && cw_strrstr(av[i], ".cor"))
		fill_champ(cw, av[i], cw->step, i);
	else
		usage(ft_printf("%w\033[1;31mInvalid file name: %s [arg#: %d]\n",
					STDERR, av[i], i), av[0]);
	return (i);
}

static int		flg_analis_2(char **av, t_cw *cw, int i, size_t j)
{
	if (av[i][j] == 'd' && !cw->f.lg.err && !cw->f.lg.dbg)
	{
		cw->f.lag |= (av[i][j + 1]) ? 0 : DEBUG;
		cw->f.lag |= (av[i][j + 1] == 'c' && !av[i][j + 2]) ? DEBUG_C : 0;
		cw->f.lag |= (av[i][j + 1] == 'r' && !av[i][j + 2]) ? DEBUG_R : 0;
		cw->f.lag |= (av[i][j + 1] == 'f' && !av[i][j + 2]) ? DEBUG_F : 0;
		cw->f.lag |= (cw->f.lg.dbg) ? 0 : FLG_ERR;
		cw->f.lag |= (cw->f.lg.vs) ? DBG_ERR : 0;
	}
	else if (av[i][j] == 'v' && !av[i][j + 1] && !cw->f.lg.err && !cw->f.lg.vs)
			cw->f.lag |= VISU;
	else if (av[i][j] == 's' && !av[i][j + 1])
		{
			cw->f.lag |= PRG_STRT;
			if (++i == cw->pos || (!(cw->start_cycle = ft_atoi(av[i])) && av[i][0] != '0'))
				usage(ft_printf("%w\033[1;31mInvalid dump size: %s [arg#: %d]\n",\
									STDERR, (i == cw->pos) ? NULL : av[i], i), av[0]);
		}
	else
		cw->f.lg.err = 1;
	if (cw->f.lg.vs_err || cw->f.lg.dbg_err)
		usage(ft_printf("%w\033[1;31mFlag '%c*' %s '%s' [arg#: %d]\n",\
			STDERR, (cw->f.lg.vs_err) ? 'v' : 'd', "do not stack with", &av[i][j], i), av[0]);
	else if (cw->f.lg.err)
		usage(ft_printf("%w\033[1;31mInvalid flag: %s [arg#: %d]\n",\
										STDERR, &av[i][j], i), av[0]);
	return (i);
}

/*
static void		flg_analis_2(char **av, t_cw *cw, int i, size_t j)
{
	if (av[i][j] == 'd' && !cw->f.lg.dbg)
	{
		if (!av[i][j + 1])
			cw->f.lag |= DEBUG;
		else if (av[i][j + 1] == 'c' && !av[i][j + 2])
			cw->f.lag |= DEBUG_C;
		else if (av[i][j + 1] == 'r' && !av[i][j + 2])
			cw->f.lag |= DEBUG_R;
		else if (av[i][j + 1] == 'f' && !av[i][j + 2])
			cw->f.lag |= DEBUG_F;
		else
			usage(ft_printf("%w\033[1;31mInvalid flag: %s [arg#: %d]\n",\
											STDERR, &av[i][j], i), av[0]);
		if (cw->f.lg.vs)
			usage(ft_printf("%w\033[1;31mFlag 'v*' %s '%s' [arg#: %d]\n",\
						STDERR, "do not stack with", &av[i][j], i), av[0]);
	}
		else if (((av[i][j] == 'v' && !av[i][j + 1]) ||\
			(av[i][j] == 'v' && av[i][j + 1] == 'd' && !av[i][j + 2])) && !cw->f.lg.vs)
		{
			cw->f.lag |= (av[i][j + 1]) ? VISU | PRG_STRT : VISU;
			if (cw->f.lg.prg_strt &&\
				(++i == cw->pos || (!(cw->vs.cycles = ft_atoi(av[i])) && av[i][0] != '0')))
				usage(ft_printf("%w\033[1;31mInvalid dump size: %s [arg#: %d]\n",\
										STDERR, (i == ac) ? NULL : av[i], i), av[0]);
			if (cw->f.lg.dbg)
				usage(ft_printf("%w\033[1;31mFlag 'd*' %s '%s' [arg#: %d]\n",\
							STDERR, "do not stack with", &av[i][j], i), av[0]);
		}

	else
		usage(ft_printf("%w\033[1;31mInvalid flag: %s [arg#: %d]\n",\
										STDERR, &av[i][j], i), av[0]);
}
*/
void			cw_flg_analis(int ac, char **av, t_cw *cw, int i)
{
	size_t		j;

	cw->pos = ac;
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
		else
			i = flg_analis_2(av, cw, i, j);
	}
}
