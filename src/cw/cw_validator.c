/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_validator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 16:47:07 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/31 18:44:48 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

static void		fill_champ(t_cw *cw, char *file_name, uint8_t id_champ, int arg)
{
	int			fd;
	uint8_t		head[HEADER_SIZE + 1];
	uint8_t		exec[CHAMP_MAX_SIZE * 2 + 1];

	if (add_champ(cw, id_champ))
		cw_out(cw, ft_printf("%w\033[1;31mPlayer# %u is already exist ",\
					STDERR, id_champ) +\
					ft_printf("%w[arg#: %d]\033[0m\n", STDERR, arg), 0);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		cw_out(cw, ft_printf("%w\033[1;31mFile %s error\033[0m\n",\
												STDERR, file_name), 0);
	if (read(fd, head, HEADER_SIZE) <= 0)
		cw_out(cw, ft_printf("%w\033[1;31mFile %s read error\033[0m\n",\
												STDERR, file_name), 0);
	if ((cw->champ[IN(cw->num_of_champs)]->head.prog_size =\
							read(fd, exec, CHAMP_MAX_SIZE * 2 + 1)) <= 0)
		cw_out(cw, ft_printf("%w\033[1;31mFile %s read error\033[0m\n",\
												STDERR, file_name), 0);
	if (cw->champ[IN(cw->num_of_champs)]->head.prog_size > CHAMP_MAX_SIZE)
		cw_out(cw, ft_printf("%w\033[1;31mFile %s %s %u > %s(%u)%s",\
			STDERR, file_name, "has too large executable code:",\
			cw->champ[IN(cw->num_of_champs)]->head.prog_size,\
			"CHAMP_MAX_SIZE", CHAMP_MAX_SIZE, "\033[0m\n"), 0);
	cw_fill_head(cw, head, exec, IN(cw->num_of_champs));
	close(fd);
}

static int		args_analis(char *arg, char **av, t_cw *cw, int i)
{
	cw->step = 0;
	if (cw->err == DUMP)
	{
		cw->f.lag |= (arg[4]) ? DUMP64 : DUMP;
		if (!av || (!(cw->cycle_to_dump = ft_atoi(av[i])) && av[i][0] != '0'))
			cw_out(cw, ft_printf("%w\033[1;31m%s %s [arg#: %d]\n",\
				STDERR, "Invalid dump size:", (av) ? av[i] : NULL, i), av[0]);
		return (i);
	}
	if (cw->err)
	{
		if (!av || ((cw->step = ft_atoi(av[i])) < 1 || MAX_PLAYERS < cw->step))
			cw_out(cw, ft_printf("%w\033[1;31m%s %s [arg#: %d]\n",\
				STDERR, "Invalid player number:",\
				(av) ? av[i] : NULL, i), av[0]);
		i++;
	}
	if (av[i] && cw_strrstr(av[i], ".cor"))
		fill_champ(cw, av[i], cw->step, i);
	else
		cw_out(cw, ft_printf("%w\033[1;31m%s %s [arg#: %d]\n",
				STDERR, "Invalid file name:", av[i], i), av[0]);
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

static int		flg_analis_1(int ac, char **av, t_cw *cw, int i)
{
	size_t		j;

	j = cw->lives;
	if (av[i][j] == 's' && !av[i][j + 1])
	{
		if (++i == ac || ((cw->f.lag |= PRG_STRT) &&\
			!(cw->start_cycle = ft_atoi(av[i])) && av[i][0] != '0'))
			cw_out(cw, ft_printf("%w\033[1;31m%s %s [arg#: %d]\n",\
							STDERR, "Invalid cycle value:",\
								(i == ac) ? NULL : av[i], i), av[0]);
	}
	else if (av[i][j] == 'e' && !av[i][j + 1])
	{
		if (++i == ac || ((cw->f.lag |= PRG_END) &&\
			!(cw->end_cycle = ft_atoi(av[i])) && av[i][0] != '0'))
			cw_out(cw, ft_printf("%w\033[1;31m%s %s [arg#: %d]\n",\
							STDERR, "Invalid cycle value:",\
								(i == ac) ? NULL : av[i], i), av[0]);
	}
	else
		flg_analis_2(av, cw, i, j);
	return (i);
}

void			cw_flg_analis(int ac, char **av, t_cw *cw, int i)
{
	size_t		j;

	while (++i < ac)
	{
		j = 0;
		while (av[i][j] == ' ' || av[i][j] == '\t' || av[i][j] == '\n')
			j++;
		if (av[i][j++] != '-' && !(cw->err = 0))
			i = args_analis(&av[i][j - 1], av, cw, i);
		else if (av[i][j] == 'n' && !av[i][j + 1] && (cw->err = 0xff))
			i = args_analis(&av[i][j], ((i + 1 < ac) ? av : NULL), cw, i + 1);
		else if ((!ft_strcmp(&av[i][j], "dump") ||\
		!ft_strcmp(&av[i][j], "dump64")) && !cw->f.lg.dump && (cw->err = DUMP))
			i = args_analis(&av[i][j], ((i + 1 < ac) ? av : NULL), cw, i + 1);
		else
		{
			cw->lives = j;
			i = flg_analis_1(ac, av, cw, i);
		}
	}
	cw->lives = 0;
}
