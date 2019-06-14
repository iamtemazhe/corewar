#include "cw.h"
#include "libft.h"

void			op_st(t_cw *cw, uint32_t i)
{
	uint32_t	pos;
	uint32_t	data;

	if (codage_validator(cw, ST, i))
		return ;
	if ((cw->map[cw->car[i].PC + OPCI_SIZE] >> 4) & IND_CODE)
	{
		pos = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE + IND_SIZE];
		pos = cw->car[i].PC + pos % IDX_MOD;
		(uint32_t)cw->map[pos] = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE];
	}
	else
	{
		data = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE + REG_SIZE];
		if (1 <= data && data <= REG_NUMBER)
			cw->car[i].reg[data - 1] = (uint32_t)cw->map[cw->car[i].PC + OPCI_SIZE + REG_SIZE];
	}
	cw->car[i].PC += cw->step;
}
