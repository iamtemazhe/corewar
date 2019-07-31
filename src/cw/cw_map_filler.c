/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_map_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:59:21 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/31 18:44:21 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "libft.h"

static void				cw_check_delimetr(t_cw *cw, uint8_t *head,\
													uint8_t i_champ, uint8_t mod)
{
	int32_t			j;
	unsigned int	size;

	j = (mod) ? MAGIC_HEADER_SIZE + PROG_NAME_LENGTH :\
							HEADER_SIZE - CHAMP_EXEC_SIZE;
	size = (head[j + 3] & 0x000000FF) << 0 |\
			(head[j + 2] & 0xFF) << 8 | (head[j + 1] & 0xFF) << 16 |\
				(head[j] & 0xFF) << 24;
	if (size)
		cw_out(cw, ft_printf("%w\033[1;31mMissing separator\033[0m\n",\
															STDERR), 0);
	if (!mod)
		return ;
	j += DELIMETR_SIZE;
	size = (head[j + 3] & 0xFF) | (head[j + 2] & 0xFF) << 8 |\
				(head[j + 1] & 0xFF) << 16 | (head[j] & 0xFF) << 24;
	if (size != cw->champ[i_champ]->head.prog_size)
		cw_out(cw, ft_printf("%w\033[1;31mChampion %s %s\033[0m\n",\
			STDERR, "has a code size that differ from what it's header says",\
							cw->champ[i_champ]->head.prog_name), 0);
}

void			cw_fill_head(t_cw *cw, uint8_t *head, uint8_t *exec, uint8_t i_champ)
{
	int32_t		j;
	int32_t		k;

	cw->champ[i_champ]->head.magic = (head[3] & 0x000000FF) << 0 |\
						(head[2] & 0xFF) << 8 | (head[1] & 0xFF) << 16 |\
						(head[0] & 0xFF) << 24;
	if (cw->champ[i_champ]->head.magic != COREWAR_EXEC_MAGIC)
		cw_out(cw, ft_printf("%w\033[1;31mInvali_champ file type\033[0m\n",\
																STDERR), 0);
	k = -1;
	j = MAGIC_HEADER_SIZE - 1;
	while (++j < MAGIC_HEADER_SIZE + PROG_NAME_LENGTH)
		cw->champ[i_champ]->head.prog_name[++k] = head[j];
	k = -1;
	cw_check_delimetr(cw, head, i_champ, 1);
	j = MAGIC_HEADER_SIZE + PROG_NAME_LENGTH + DELIMETR_SIZE * 2 - 1;
	while (++j < HEADER_SIZE - CHAMP_EXEC_SIZE)
		cw->champ[i_champ]->head.comment[++k] = head[j];
	cw_check_delimetr(cw, head, i_champ, 0);
	if (!(cw->champ[i_champ]->exec = (uint8_t*)malloc(sizeof(uint8_t) *\
									(cw->champ[i_champ]->head.prog_size + 1))))
		cw_out(cw, ft_printf("%w\033[1;31mError\033[0m\n",\
												STDERR), 0);
	ft_memcpy(cw->champ[i_champ]->exec, exec,\
						cw->champ[i_champ]->head.prog_size);
}

static void			fill_map(t_cw *cw)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	while (i < cw->num_of_champs)
	{
		j = 0;
		k = (MEM_SIZE / cw->num_of_champs) * i;
		while (j < cw->champ[i]->head.prog_size)
		{
			cw->map[k].v.code = cw->champ[i]->exec[j++];
			cw->map[k++].v.col = cw->champ[i]->id;
		}
		j = (MEM_SIZE / cw->num_of_champs) * (i + 1);
		while (k < j)
			cw->map[k++].v.col = COL_CODE;
		i++;
	}
}

static void			sort_champs(t_cw *cw)
{
	uint8_t			i;
	uint8_t			j;
	uint8_t			id;
	t_champ			*tmp;

	id = cw->num_of_champs;
	i = cw->num_of_champs;
	while (i-- > 0 && id > 0)
		if (!cw->champ[i]->id)
		{
			j = cw->num_of_champs;
			while (j-- > 0 && id > 0)
				if (cw->champ[j]->id == id && (j = cw->num_of_champs))
					id--;
			cw->champ[i]->id = id;
		}
	i = 0;
	while (++i < cw->num_of_champs)
	{
		tmp = cw->champ[i];
		j = i;
		while (j-- > 0 && cw->champ[j]->id > tmp->id)
			cw->champ[j + 1] = cw->champ[j];
		cw->champ[j + 1] = tmp;
	}
}

void				cw_map_filler(int ac, char **av, t_cw *cw)
{
	if (ac == 1)
		cw_out(cw, 0, av[0]);
	cw_flg_analis(ac, av, cw, 0);
	sort_champs(cw);
	if (!cw->num_of_champs)
		cw_out(cw, ft_printf("%w\033[1;31mWhere is players O_o?\n",\
													STDERR), av[0]);
	if (cw->num_of_champs > MAX_PLAYERS)
		cw_out(cw, ft_printf("%w\033[1;31mThe number of players (%u) ",\
					STDERR, cw->num_of_champs) +
				ft_printf("%wis more than MAX_PLAYERS (%u)\n",\
					STDERR, MAX_PLAYERS), av[0]);
	fill_map(cw);
}
