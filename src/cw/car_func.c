#include "cw.h"
#include "libft.h"

static t_car		*new_car(uint32_t id_champ)
{
	t_car			*new_car;
	static uint8_t	id_car = 0;

	if (!(new_car = (t_car *)malloc(sizeof(t_car))))
		return (NULL);
	new_car->id = ++id_car;
	new_car->carry = 0;
	new_car->op_code = 0;
	new_car->last_live = 0;
	new_car->cycle_to_wait = 0;
	new_car->pc = 0;
	ft_bzero(new_car->reg, REG_NUMBER * sizeof(uint32_t));
	new_car->reg[0] = -id_champ;
	return (new_car);
}

uint8_t				add_car(t_cw *cw, uint8_t i_car)
{
	if (!cw->car)
	{
		cw->num_of_cars = cw->num_of_champs;
		if (!(cw->car = (t_car **)malloc(sizeof(t_car *) * cw->num_of_cars)))
			exit (ft_puterr(-1, "Error"));
		while (i_car < cw->num_of_cars)
		{
			if (!(cw->car[i_car] = new_car(i_car + 1)))
				exit (ft_puterr(-1, "Error"));
			i_car++;
		}
		return (IN(cw->num_of_cars));
	}
	cw->num_of_cars++;
	if (!(cw->car = (t_car **)realloc(cw->car, sizeof(t_car *) * cw->num_of_cars)))
		exit (ft_puterr(-1, "Error"));
	if (!(cw->car[IN(cw->num_of_cars)] = new_car(0)))
		exit (ft_puterr(-1, "Error"));
	cw->car[IN(cw->num_of_cars)]->carry = cw->car[i_car]->carry;
	cw->car[IN(cw->num_of_cars)]->last_live = cw->car[i_car]->last_live;
	ft_memcpy(cw->car[IN(cw->num_of_cars)]->reg, cw->car[i_car]->reg, REG_NUMBER * sizeof(uint32_t));
	return (IN(cw->num_of_cars));
}

static void			del_one_car(t_cw *cw, uint8_t i_car)
{
	free(cw->car[i_car]);
	cw->car[i_car] = NULL;
}

void				del_car(t_cw *cw, uint8_t i_car)
{
	del_one_car(cw, i_car);
	while (++i_car < cw->num_of_cars)
	{
		cw->car[IN(i_car)] = cw->car[i_car];
		cw->car[i_car] = NULL;
	}
	cw->num_of_cars--;
	ft_printf("\033[3%1um!!!!!!!!!!!!!!!!!!CARRY DEAD!!!!!!!!!!!!!!!!!\n\n", i_car % 6 + 1);
}

void				del_all_cars(t_cw *cw)
{
	while (cw->num_of_cars-- > 0)
		del_one_car(cw, cw->num_of_cars);
	free(cw->car);
	cw->car = NULL;
}