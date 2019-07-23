#include "cw.h"
#include "libft.h"

static t_champ		*new_champ(uint8_t id_champ)
{
	t_champ			*new_champ;

	if (!(new_champ = (t_champ *)malloc(sizeof(t_champ))))
		return (NULL);
	new_champ->id = id_champ;
	new_champ->lives = 0;
	return (new_champ);
}

int8_t				add_champ(t_cw *cw, uint8_t id_champ)
{
	uint8_t			i;

	i = 0;
	while (i < cw->num_of_champs && id_champ)
		if (cw->champ[i++]->id == id_champ)
			return (-1);
	if (!(cw->champ = (t_champ **)realloc(cw->champ, sizeof(t_champ *) *\
													++cw->num_of_champs)))
		exit(ft_printf("%w\033[1;31mError\033[0m\n", STDERR));
	if (!(cw->champ[IN(cw->num_of_champs)] = new_champ(id_champ)))
		exit(ft_printf("%w\033[1;31mError\033[0m\n", STDERR));
	return (0);
}

static void			del_one_champ(t_cw *cw, size_t i_champ)
{
	free(cw->champ[i_champ]);
	cw->champ[i_champ] = NULL;
}

void				del_all_champs(t_cw *cw)
{
	while (cw->num_of_champs-- > 0)
		del_one_champ(cw, cw->num_of_champs);
	free(cw->champ);
	cw->champ = NULL;
}
