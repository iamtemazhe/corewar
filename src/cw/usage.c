#include "cw.h"
#include "libft.h"

void			usage(uint8_t err_n, const char *str, size_t size)
{
	if (err_n == 1)
		ft_puterr(0, "Invalid dump");
	else if (err_n == 2)
		ft_puterr(0, "Invalid player number");
	else if (err_n == 3)
	{
		write(2, "Invalid file name ", 18);
		ft_puterr(0, str);
	}
	else if (err_n == 4)
		err_n = 0;	
	if (size)
		return ;
	exit(ft_printf("Usage: ./corewar <champion1.cor> <...>\n"));
}
