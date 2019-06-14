#include "cw.h"
#include "libft.h"

void			op_ld(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;

	if (codage_validator(cw, LD, i))
		return ;
	if ((cw->map[cw->car[i].PC + OPCI_SIZE] >> 6) & IND_CODE)
	{
		pos = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + IND_SIZE];
		data = (uint32_t)cw->map[cw->car[i].PC + pos % IDX_MOD];
		pos = cw->car[i].PC + OPCI_SIZE + IND_SIZE + REG_SIZE;
	}
	else
	{
		data = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + cw->op[LD].label_size];
		pos = cw->car[i].PC + OPCI_SIZE + cw->op[LD].label_size + REG_SIZE;
	}
	(uint32_t)cw->map[pos] = data;
	cw->car[i].carry = (data) ? 0 : 1;
	cw->car[i].PC += cw->step;
}
