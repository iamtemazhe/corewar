/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/06/12 19:44:02 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor_op.h"

void			error_func(char *str)
{
	ft_printf("ERROR:\n%s\n", str);
	exit(0);
}

int				main(int ac, char **av)
{
	t_cw		cw;
	uint		j;

	if (ac == 1)
		return (ft_printf("Usage: ./corewar <champion1.cor> <...>\n"));
	cw.num_champs = 0;
	cw.flg = 0;
	cw.cycles_to_die = 0;
	parse_args(ac, av, &cw);
	fill_champ_id(&cw);
	if (!cw.num_champs)
		error_func("The number of players must be 2 or more");
	if (cw.num_champs > MAX_PLAYERS)
		error_func("The number of players is more than MAX_PLAYERS");
	fill_map(&cw);
	j = 0;
	ft_printf("num_champs = %d\n", cw.num_champs);
	while (j < cw.num_champs)
	{
		ft_printf("name = %s\n", cw.champ[j].head.prog_name);
		ft_printf("comment = %s\n", cw.champ[j].head.comment);
		ft_printf("id = %d\n", cw.champ[j].id);
		j++;
	}
	// ft_printf("cw->cycles_to_die = %d\n", cw.cycles_to_die);
	// j = 0;
    // while (j < 4096)
    // {
    //     ft_printf("%x", cw.map[j]);
	// 	j++;
    // }
	return (1);
}