/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:59:21 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/01 14:46:56 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "op.h"
#include "libft.h"

void			fill_map(t_cw *cw)
{
	uint		i;
	uint		j;
	uint		k;

	i = 0;
	ft_bzero(cw->map, MEM_SIZE);
	while (i < cw->num_of_champs)
	{
		j = 0;
		k = (MEM_SIZE / cw->num_of_champs) * i;
		while (j < cw->champ[i].head.prog_size)
		{
			cw->map[k++] = cw->champ[i].exec[j];
			j++;
		}
		i++;
	}
}

uint8_t			*write_exec(char *buf, int size)
{
	uint8_t		*exec;
	int			i;

	if (!(exec = (uint8_t*)malloc(sizeof(uint8_t) * (size + 1))))
		exit(ft_printf("Malloc error\n"));
	i = -1;
	while (++i < size)
		exec[i] = buf[i];
	return (exec);
}

void			fill_head(char *head, char *exec, int id, t_cw *cw)
{
	int			j;
	int			k;

	j = 3;
	k = -1;
	cw->champ[id].head.magic = (head[3] & 0x000000FF) << 0 |\
						(head[2] & 0xFF) << 8 | (head[1] & 0xFF) << 16 |\
						(head[0] & 0xFF) << 24;
	if (cw->champ[id].head.magic != COREWAR_EXEC_MAGIC)
		exit(ft_printf("Invalid file type\n"));
	while (++j < 132)
		cw->champ[id].head.prog_name[++k] = head[j];
	k = -1;
	j = 139;
	while (++j < 2188)
		cw->champ[id].head.comment[++k] = head[j];
	cw->champ[id].exec = write_exec(exec, cw->champ[id].head.prog_size);
}

void			fill_champ(char *av, int j, t_cw *cw)
{
	int			fd;
	char		head[2193];
	char		exec[CHAMP_MAX_SIZE + 1];

	if (j > (int)cw->num_of_champs || cw->champ[j - 1].id)
		exit(ft_printf("Invalid player number\n"));
	cw->champ[j - 1].id = j;
	if ((fd = open(av, O_RDONLY)) < 0)
		exit(ft_printf("File read error\n"));
	if (read(fd, head, 2192) <= 0)
		exit(ft_printf("File read error\n"));
	cw->champ[j - 1].head.prog_size = read(fd, exec, CHAMP_MAX_SIZE + 1);
	if (cw->champ[j - 1].head.prog_size <= 0)
		exit(ft_printf("File read error\n"));
	if (cw->champ[j - 1].head.prog_size > CHAMP_MAX_SIZE)
		exit(ft_printf("File %s has too large executable code\n", av));
	fill_head(head, exec, j - 1, cw);
	close(fd);
}

int				find_id(t_cw *cw)
{
	uint		i;
	int			t[cw->num_of_champs + 1];

	i = 0;
	while (++i <= cw->num_of_champs)
		t[i - 1] = (cw->champ[i - 1].id) ? 1 : 0;
	i = 0;
	while (++i <= cw->num_of_champs)
		if (!t[i])
			break ;
	return (i + 1);
}

void			check_champ_id(t_cw *cw, int ac, char **av)
{
	int			i;

	i = 0;
	if (!(cw->flg & N))
	{
		while (++i < ac)
			if (ft_strrstr(av[i], ".cor"))
				fill_champ(av[i], i, cw);
	}
	else
	{
		while (++i < ac)
			if (!(ft_strcmp(av[i], "-n")))
			{
				fill_champ(av[i + 2], ft_atoi(av[i + 1]), cw);
				i += 2;
			}
		i = 0;
		while (++i < ac)
			if (!(ft_strcmp(av[i], "-n")))
				i += 2;
			else if (ft_strrstr(av[i], ".cor"))
				fill_champ(av[i], find_id(cw), cw);
	}
}

void			parse_args(int ac, char **av, t_cw *cw, int i)
{
	while (++i < ac)
		if (!(ft_strcmp(av[i], "-v")))
			cw->flg |= VISU;
		else if (!(ft_strcmp(av[i], "-dump")))
		{
			cw->flg |= DUMP;
			if ((cw->cycle_to_dump = ft_atoi(av[++i])) <= 0)
				exit(ft_printf("Invalid dump\n"));
		}
		else if (!(ft_strcmp(av[i], "-n")))
		{
			cw->flg |= N;
			if (++i >= ac || ft_atoi(av[i]) < 1)
				exit(ft_printf("Invalid player number\n"));
			if (++i < ac && ft_strrstr(av[i], ".cor"))
				cw->num_of_champs++;
			else
				exit(ft_printf("Invalid file name %s\n", av[i]));
		}
		else if (ft_strrstr(av[i], ".cor"))
			cw->num_of_champs++;
		else
			exit(ft_printf("Invalid file name %s\n", av[i]));
}

void			fill_cw(int ac, char **av, t_cw *cw)
{
	uint		i;

	i = 1;
	if (ac == 1)
		exit(ft_printf("Usage: ./corewar <champion1.cor> <...>\n"));
	cw->num_of_champs = 0;
	cw->flg = 0;
	cw->cycle_to_dump = 0;
	parse_args(ac, av, cw, 0);
	if (!cw->num_of_champs)
		exit(ft_printf("Where is players O_o?\n"));
	if (cw->num_of_champs > MAX_PLAYERS)
		exit(ft_printf("The number of players is more than MAX_PLAYERS\n"));
	if (!(cw->champ = (t_champ*)malloc(sizeof(t_champ) * cw->num_of_champs)))
		exit(ft_printf("Malloc error\n"));
	while (++i <= cw->num_of_champs)
		cw->champ[i - 1].id = 0;
	check_champ_id(cw, ac, av);
	fill_map(cw);
}
