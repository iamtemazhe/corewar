/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:59:21 by hgysella          #+#    #+#             */
/*   Updated: 2019/06/14 18:59:45 by hgysella         ###   ########.fr       */
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

void			check_champ_id(t_cw *cw)
{
	uint		i;
	uint		j;

	i = 0;
	if (!(cw->flg & N))
		while (++i <= cw->num_of_champs)
			cw->champ[i - 1].id = i;
	else
		while (++i <= cw->num_of_champs)
		{
			if (cw->champ[i - 1].id > cw->num_of_champs)
				error_func("Invalid player number");
			j = 0;
			while (++j <= cw->num_of_champs)
				if (cw->champ[i - 1].id == cw->champ[j - 1].id && i != j)
					error_func("Invalid player number");
		}
}

void			fill_champ_id(t_cw *cw)
{
	uint		i;
	uint		j;
	int			t[cw->num_of_champs + 1];

	i = 0;
	ft_bzero(t, (cw->num_of_champs + 1) * 4);
	while (++i <= cw->num_of_champs)
		t[cw->champ[i - 1].id] = (cw->champ[i - 1].id) ? 1 : 0;
	i = 0;
	while (++i <= cw->num_of_champs)
		if (!cw->champ[i - 1].id)
		{
			j = 0;
			while (++j <= cw->num_of_champs)
				if (!t[j])
				{
					t[j] = 1;
					break ;
				}
			cw->champ[i - 1].id = j;
		}
}

uint8_t			*write_exec(char *buf, int size)
{
	uint8_t		*exec;
	int			i;

	if (!(exec = (uint8_t*)malloc(sizeof(uint8_t) * (size + 1))))
		error_func("Malloc error");
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
		error_func("Invalid file type");
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
	uint		n;

	cw->num_of_champs++;
	n = cw->num_of_champs;
	cw->champ = (n == 1) ? (t_champ*)malloc(sizeof(t_champ) * n) :\
							(t_champ*)realloc(cw->champ, sizeof(t_champ) * n);
	cw->champ[n - 1].id = j;
	if ((fd = open(av, O_RDONLY)) < 0)
		error_func("File read error");
	if (read(fd, head, 2192) <= 0)
		error_func("File read error");
	cw->champ[n - 1].head.prog_size = read(fd, exec, CHAMP_MAX_SIZE + 1);
	if (cw->champ[n - 1].head.prog_size <= 0)
		error_func("File read error");
	if (cw->champ[n - 1].head.prog_size > CHAMP_MAX_SIZE)
		error_func("File has too large code");
	fill_head(head, exec, cw->num_of_champs - 1, cw);
	close(fd);
}

void			parse_args(int ac, char **av, t_cw *cw)
{
	int			i;
	int			n;

	i = 0;
	while (++i < ac)
		if (!(ft_strcmp(av[i], "-v")))
			cw->flg |= VISU;
		else if (!(ft_strcmp(av[i], "-dump")))
		{
			cw->flg |= DUMP;
			if ((cw->cycle_to_dump = ft_atoi(av[++i])) <= 0)
				error_func("Invalid dump");
		}
		else if (!(ft_strcmp(av[i], "-n")))
		{
			cw->flg |= N;
			if (++i >= ac || (n = ft_atoi(av[i])) < 1)
				error_func("Invalid player number");
			if (ft_strrstr(av[++i], ".cor"))
				fill_champ(av[i], n, cw);
			else
				error_func("Invalid file name");
		}
		else if (ft_strrstr(av[i], ".cor"))
			fill_champ(av[i], 0, cw);
		else
			error_func("Invalid file name");
}

void			fill_cw(int ac, char **av, t_cw *cw)
{
	if (ac == 1)
		error_func("Usage: ./corewar <champion1.cor> <...>\n");
	cw->num_of_champs = 0;
	cw->flg = 0;
	cw->cycle_to_dump = 0;
	parse_args(ac, av, cw);
	check_champ_id(cw);
	if (cw->flg & N)
		fill_champ_id(cw);
	if (!cw->num_of_champs)
		error_func("The number of players must be 2 or more");
	if (cw->num_of_champs > MAX_PLAYERS)
		error_func("The number of players is more than MAX_PLAYERS");
	fill_map(cw);
}
