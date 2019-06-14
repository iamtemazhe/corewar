/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgysella <hgysella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:00:28 by hgysella          #+#    #+#             */
/*   Updated: 2019/06/14 19:01:47 by hgysella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "op.h"
#include "libft.h"

void			error_func(char *str)
{
	ft_printf("ERROR:\n%s\n", str);
	exit(0);
}

int				main(int ac, char **av)
{
	t_cw		cw;
	uint		j;

	fill_cw(ac, av, &cw);
	j = 0;
	ft_printf("num_of_champs = %d\n", cw.num_of_champs);
	while (j < cw.num_of_champs)
	{
		ft_printf("name = %s\n", cw.champ[j].head.prog_name);
		ft_printf("comment = %s\n", cw.champ[j].head.comment);
		ft_printf("id = %d\n", cw.champ[j].id);
		j++;
	}
	ft_printf("cw->cycle_to_dump = %d\n", cw.cycle_to_dump);
	// j = 0;
    // while (j < 4096)
    // {
    //     ft_printf("%x", cw.map[j]);
	// 	j++;
    // }
	return (1);
}
