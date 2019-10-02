#include "vm.h"

static void        parse_flag(t_corewar *cw, char *flag)
{
	if (ft_strlen(flag != 2))
		send_error("Empty flag.\n");
	flag++;
	if (*flag == 'd')
		cw->flag |= FL_DUMP;
	else if (*flag == 'g')
		cw->flag |= FL_GUI;
	else if (*flag == 'n')
		cw->flag |= FL_PLAYER;
}

static void        corewar_parser(t_corewar *cw, int ac, char **av)
{
	int32_t		i;

	i = -1;
	while (++i < ac)
	{
		if (cw->flag & FL_DUMP)
			parse_dump(cw, av[i]);
		else if (cw->flag & FL_PLAYER)
			parse_player(cw, );
		else if (av[i][0] == '-')
			parse_flag(cw, av[i]);
	}
}

void                corewar(int ac, char **av)
{
	t_corewar	cw;

	bzero(cw, sizeof(t_corewar));
	corewar_parser(&cw, ac, av);
}