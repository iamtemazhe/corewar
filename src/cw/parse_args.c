/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:59:21 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/24 12:34:28 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "libft.h"

void			fill_map(t_cw *cw)
{
	uint		i;
	uint		j;
	uint		k;

	i = 0;
	while (i < cw->num_of_champs)
	{
		j = 0;
		k = (MEM_SIZE / cw->num_of_champs) * i;
		while (j < cw->champ[i]->head.prog_size)
		{
			cw->map[k].v.code = cw->champ[i]->exec[j++];
			cw->map[k++].v.col = cw->champ[i]->id * 2 - 1;
		}
		i++;
	}
}

uint8_t			*write_exec(uint8_t *buf, size_t size)
{
	uint8_t		*exec;
	size_t		i;

	if (!(exec = (uint8_t*)malloc(sizeof(uint8_t) * (size + 1))))
		exit(ft_printf("%w\033[1;31mError\033[0m\n", STDERR));
	i = 0;
	while (i < size)
	{
		exec[i] = buf[i];
		i++;
	}
	return (exec);
}

void			fill_head(t_cw *cw, uint8_t *head, uint8_t *exec,\
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
	cw->champ[i_champ]->exec = write_exec(exec,\
								cw->champ[i_champ]->head.prog_size);
}

void			fill_champ(t_cw *cw, char *file_name, uint8_t id_champ, int arg)
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
	if (av[i] && ft_strrstr(av[i], ".cor"))
		fill_champ(cw, av[i], cw->step, i);
	else
		usage(ft_printf("%w\033[1;31mInvalid file name: %s [arg#: %d]\n",
					STDERR, av[i], i), av[0]);
	return (i);
}

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
			usage(ft_printf("%w\033[1;31mInvalid flag:\
							%s [arg#: %d]\n", STDERR, &av[i][j], i), av[0]);
		if (cw->f.lg.vs)
			usage(ft_printf("%w\033[1;31mFlag 'vs' do not stack with '%s'\
								[arg#: %d]\n", STDERR, &av[i][j], i), av[0]);
	}
	else
		usage(ft_printf("%w\033[1;31mInvalid flag:\
								%s [arg#: %d]\n", STDERR, &av[i][j], i), av[0]);
}

static void		flg_analis(int ac, char **av, t_cw *cw, int i)
{
	size_t		j;

	cw->f.lag = 0;
	cw->num_of_champs = 0;
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
		else if (av[i][j] == 'v' && !av[i][j + 1] && !cw->f.lg.vs)
		{
			cw->f.lag |= VISU;
			if (cw->f.lg.dbg)
				usage(ft_printf("%w\033[1;31mFlag 'd.' do not stack with '%s'\
							[arg#: %d]\n", STDERR, &av[i][j], i), av[0]);
		}
		else if ((!ft_strcmp(&av[i][j], "dump") ||\
		!ft_strcmp(&av[i][j], "dump64")) && !cw->f.lg.dump && (cw->err = DUMP))
			i = args_analis(&av[i][j], ((i + 1 < ac) ? av : NULL), cw, i + 1);
		else
			flg_analis_2(av, cw, i, j);
	}
}

static void		sort_champs(t_cw *cw)
{
	int			i;
	int			j;
	uint8_t		id;
	t_champ		*tmp;

	id = cw->num_of_champs;
	i = cw->num_of_champs;
	while (--i >= 0 && id > 0)
		if (!cw->champ[i]->id)
		{
			j = cw->num_of_champs;
			while (--j >= 0 && id > 0)
				if (cw->champ[j]->id == id && (j = cw->num_of_champs))
					id--;
			cw->champ[i]->id = id;
		}
	i = 0;
	while (++i < cw->num_of_champs)
	{
		tmp = cw->champ[i];
		j = i;
		while (--j >= 0 && cw->champ[j]->id > tmp->id)
			cw->champ[j + 1] = cw->champ[j];
		cw->champ[j + 1] = tmp;
	}
}

void			fill_cw(int ac, char **av, t_cw *cw)
{
	if (ac == 1)
		usage(0, av[0]);
	flg_analis(ac, av, cw, 0);
	sort_champs(cw);
	if (!cw->num_of_champs)
		usage(ft_printf("%w\033[1;31mWhere is players O_o?\n", STDERR), av[0]);
	if (cw->num_of_champs > MAX_PLAYERS)
		usage(ft_printf("%w\033[1;31mThe number of players (%u) ",\
					STDERR, cw->num_of_champs) +
				ft_printf("%wis more than MAX_PLAYERS (%u)\n",\
					STDERR, MAX_PLAYERS), av[0]);
	fill_map(cw);
}
