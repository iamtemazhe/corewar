#include "cw.h"
#include "libft.h"

inline void		usage(int prnt, char *prog_name)
{
	ft_printf("\033[1;30mUsage: %s [-dump N | -dump64 N] [-d | -dc | -v] [-a] [-n N] <champion.cor> <...>\n", prog_name);
	ft_printf("*********************** PROGRAMM FLAGS ********************************\n");
	ft_printf("| -a            : Prints output from \"aff\" (default is to hide it)    |\n");
	ft_printf("| -n N <*.cor>  : Sets champion number (from 1) for <champion.cor>    |\n");
	ft_printf("********************* TEXT OUTPUT MODE ********************************\n");
	ft_printf("| -dump N       : Dumps memory by 32 octets after N cycles then exits |\n");
	ft_printf("| -dump64 N     : Dumps memory by 64 octets after N cycles then exits |\n");
	ft_printf("********************* VISUAL OUTPUT MODE ******************************\n");
	ft_printf("| -d            : Debug mode                                          |\n");
	ft_printf("| -dc           : Debug mode with cycles                              |\n");
	ft_printf("| -dr           : Debug mode with car death                           |\n");
	ft_printf("| -df           : Debug mode with all modifications                   |\n");
	ft_printf("| -v            : Visual (by Ncurses) output mode                     |\n");
	ft_printf("***********************************************************************\033[0m\n");
	exit((prnt) ? -1 : 0);
}

void			dump(t_cw *cw)
{
	size_t		i;
	uint8_t		num_of_oct;

	i = 0;
	num_of_oct = (cw->f.lg.dump64) ? 64 : 32;
	while (i < MEM_SIZE)
	{
		if (!(i % num_of_oct))
			ft_printf("0x%04zx : ", i);
		ft_printf("%02x%c", cw->map[i].v.code, ((i % num_of_oct) == num_of_oct - 1) ? '\n' : ' ');
		i++;
	}
	exit(0);
}
