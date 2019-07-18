/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:59:21 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/18 18:06:21 by jwinthei         ###   ########.fr       */
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
		while (j < cw->champ[i].head.prog_size)
			cw->map[k++] = cw->champ[i].exec[j++];
		i++;
	}
}

uint8_t			*write_exec(unsigned char *buf, int size)
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

void			fill_head(unsigned char *head, unsigned char *exec, int id, t_cw *cw)
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
	int				fd;
	unsigned char	head[2193];
	unsigned char	exec[CHAMP_MAX_SIZE + 1];

	if (j > (int)cw->num_of_champs || cw->champ[j - 1].id)
		exit(ft_printf("Invalid player number\n"));
	cw->champ[j - 1].id = j;
	if ((fd = open(av, O_RDONLY)) < 0)
		exit(ft_puterr(-1, "File read error"));
	if (read(fd, head, 2192) <= 0)
		exit(ft_puterr(-1, "File read error"));
	cw->champ[j - 1].head.prog_size = read(fd, exec, CHAMP_MAX_SIZE + 1);
	if (cw->champ[j - 1].head.prog_size <= 0)
		exit(ft_puterr(-1, "File read error"));
	if (cw->champ[j - 1].head.prog_size > CHAMP_MAX_SIZE)
		exit(ft_printf("File %s has too large executable code, %d > %d\n", av, cw->champ[j - 1].head.prog_size, CHAMP_MAX_SIZE));
	fill_head(head, exec, j - 1, cw);
	close(fd);
}

static int		find_id(t_cw *cw)
{
	uint32_t	i;
	uint32_t	t[cw->num_of_champs + 1];

	i = 0;
	while (++i <= cw->num_of_champs)
		t[i - 1] = (cw->champ[i - 1].id) ? 1 : 0;
	i = 0;
	while (++i <= cw->num_of_champs)
		if (!t[i])
			break ;
	return (i + 1);
}

static void		check_champ_id(t_cw *cw, int ac, char **av)
{
	int32_t		i;

	i = 0;
	if (!(cw->flg & N))
	{
		while (++i < ac)
			if (ft_strrstr(av[i], ".cor"))
				fill_champ(av[i], i, cw);
		return ;
	}
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

static void		parse_args(int ac, char **av, t_cw *cw, int i)
{
	while (++i < ac)
		if (!(ft_strncmp(av[i], "-v", 2)))
			cw->flg |= VISU;
		else if (!(ft_strncmp(av[i], "-dump", 5)) || !(ft_strncmp(av[i], "-d", 2)))
		{
			cw->flg |= (av[i][2]) ? DUMP32 : DUMP64;
			if (++i >= ac || (cw->cycle_to_dump = ft_atoi(av[i])) <= 0)
				usage(1, 0, 0);
		}
		else if (!(ft_strncmp(av[i], "-n", 2)))
		{
			cw->flg |= N;
			if (++i >= ac || (cw->step = ft_atoi(av[i])) < 1 || cw->step > 4)
				usage(2, 0, 0);
			if (++i < ac && ft_strrstr(av[i], ".cor"))
				cw->num_of_champs++;
			else
				usage(3, av[i], 0);
		}
		else if (ft_strrstr(av[i], ".cor"))
			cw->num_of_champs++;
		else
			usage(3, av[i], 0);
}

void			fill_cw(int ac, char **av, t_cw *cw)
{
	uint32_t	i;

	if (ac == 1)
		usage(0, 0, 0);
	parse_args(ac, av, cw, 0);
	if (!cw->num_of_champs)
		exit(ft_puterr(-1, "Where is players O_o?"));
	if (cw->num_of_champs > MAX_PLAYERS)
		exit(ft_puterr(-1, "The number of players is more than MAX_PLAYERS"));
	if (!(cw->champ = (t_champ*)malloc(sizeof(t_champ) * cw->num_of_champs)))
		exit(ft_puterr(-1, "Error"));
	i = 0;
	while (i < cw->num_of_champs)
		cw->champ[i++].id = 0;
	check_champ_id(cw, ac, av);
	fill_map(cw);
}
