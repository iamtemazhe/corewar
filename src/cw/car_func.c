#include "cw.h"
#include "libft.h"

static int8_t		new_car(t_cw *cw, uint8_t i_car)
{
	t_car			*new_car;

	if (!(new_car = (t_car *)malloc(sizeof(t_car))))
		return (-1);
	new_car->id = i_car + 1;
	new_car->carry = 0;
	new_car->op_code = 0;
	new_car->last_live = 0;
	new_car->cycle_to_wait = 0;
	new_car->pc = 0;
	ft_bzero(new_car->reg, REG_NUMBER * sizeof(int32_t));
	cw->car[i_car] = new_car;
	return (0);
}

void				add_car(t_cw *cw, uint8_t i_car)
{
	if (!cw->car)
	{
		cw->num_of_cars = cw->num_of_champs;
		if (!(cw->car = (t_car **)malloc(sizeof(t_car *) * cw->num_of_cars)))
			exit (ft_puterr(-1, "Error"));
		while (i_car < cw->num_of_cars)
			if (new_car(cw, i_car++))
				exit (ft_puterr(-1, "Error"));
		return ;
	}
	if (!(cw->car = (t_car **)realloc(cw->car, sizeof(t_car *) * ++cw->num_of_cars)))
		exit (ft_puterr(-1, "Error"));
	if (new_car(cw, IN(cw->num_of_cars)))
		exit (ft_puterr(-1, "Error"));
	cw->car[IN(cw->num_of_cars)]->carry = cw->car[i_car]->carry;
	cw->car[IN(cw->num_of_cars)]->last_live = cw->car[i_car]->last_live;
	ft_memcpy(cw->car[IN(cw->num_of_cars)]->reg, cw->car[i_car]->reg, REG_NUMBER * sizeof(int32_t));
}

void				del_all_cars(t_cw *cw)
{
	while (cw->num_of_cars-- > 0)
		free(cw->car[cw->num_of_cars]);
	free(cw->car);
}

void				del_car(t_cw *cw, uint8_t i_car)
{
	free(cw->car[i_car]);
	while (++i_car < cw->num_of_cars)
			cw->car[IN(i_car)] = cw->car[i_car];
	cw->num_of_cars--;
}