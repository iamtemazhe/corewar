/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 14:58:38 by jwinthei          #+#    #+#             */
/*   Updated: 2019/07/30 15:39:37 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

static t_car		*new_car(t_cw *cw, uint8_t id_champ, int32_t pc)
{
	t_car			*new_car;
	static size_t	id_car = 0;

	if (!(new_car = (t_car *)malloc(sizeof(t_car))))
		return (NULL);
	new_car->id = ++id_car;
	new_car->carry = 0;
	new_car->op_code = 0;
	new_car->last_live = 0;
	new_car->cycle_to_wait = 0;
	new_car->pc = pc;
	ft_bzero(new_car->reg, REG_NUMBER * sizeof(uint32_t));
	new_car->reg[0] = -id_champ;
	if (cw->f.lg.vs)
		vs_backlight_on_car(cw, id_champ, pc, 1);
	return (new_car);
}

static void			init_cars(t_cw *cw, size_t i_car)
{
	cw->num_of_cars = cw->num_of_champs;
	cw->max_num_of_cars = cw->num_of_cars;
	if (!(cw->car = (t_car **)malloc(sizeof(t_car *) * cw->num_of_cars)))
		cw_out(cw, ft_printf("%w\033[1;31mCars malloc error\033[0m\n", STDERR), 0);
	while (i_car < cw->num_of_cars)
	{
		if (!(cw->car[i_car] = new_car(cw, cw->champ[i_car]->id,\
									(MEM_SIZE / cw->num_of_cars) * i_car)))
			cw_out(cw, ft_printf("%w\033[1;31mNew car Malloc error\033[0m\n",\
																		STDERR), 0);
		i_car++;
	}
}

void				add_car(t_cw *cw, size_t i_car, int32_t pc)
{
	if (!cw->car)
	{
		init_cars(cw, i_car);
		return ;
	}
	if (++cw->num_of_cars > cw->max_num_of_cars)
	{
		if (!(cw->car = (t_car **)realloc(cw->car,\
									sizeof(t_car *) * cw->num_of_cars)))
			cw_out(cw, ft_printf("%w\033[1;31mCars malloc error\033[0m\n", STDERR), 0);
		cw->max_num_of_cars = cw->num_of_cars;
	}
	if (!(cw->car[cw->num_of_cars - 1] = new_car(cw,\
									-cw->car[i_car]->reg[0], pc)))
		cw_out(cw, ft_printf("%w\033[1;31mNew car malloc error\033[0m\n", STDERR), 0);
	cw->car[cw->num_of_cars - 1]->carry = cw->car[i_car]->carry;
	cw->car[cw->num_of_cars - 1]->last_live = cw->car[i_car]->last_live;
	ft_memcpy(cw->car[cw->num_of_cars - 1]->reg, cw->car[i_car]->reg,\
										REG_NUMBER * sizeof(int32_t));
}

static void			del_one_car(t_cw *cw, size_t i_car)
{
	if (cw->f.lg.dbg_r)
		ft_printf("%38\033[3%1um|%9s Carry# %7u DEAD! %2|\n\r",\
					cw->car[i_car]->id % 6 + 1, "", cw->car[i_car]->id);
	else if (cw->f.lg.vs)
	{
		vs_backlight_car(cw, i_car, 0, 0);
		if (cw->f.lg.vs_audio)
			vs_audio(0);			
	}
	free(cw->car[i_car]);
	cw->car[i_car] = NULL;
	cw->num_of_cars--;
}

void				del_cars(t_cw *cw)
{
	size_t		i_car;
	size_t		first_car;
	size_t		num_of_cars;

	i_car = cw->num_of_cars;
	num_of_cars = cw->num_of_cars;
	while (i_car-- > 0)
		if ((int32_t)(cw->cycles - cw->car[i_car]->last_live) >=\
												cw->cycle_to_die)
		{
			del_one_car(cw, i_car);
			first_car = i_car;
		}
	i_car = first_car;
	while (++first_car < num_of_cars)
		if (cw->car[first_car])
		{
			cw->car[i_car++] = cw->car[first_car];
			cw->car[first_car] = NULL;
		}
	if (cw->num_of_cars != num_of_cars)
		mvwprintw(cw->vs.header, 8, 13, "%-7u", cw->num_of_cars);
}
