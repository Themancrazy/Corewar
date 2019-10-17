#include "vm.h"

/*
** ----------------------------------------------------------------------------
** Function that handles the '-d' flag and assigns a dump_cycle at av[dump_arg]
** cycle.
**
** {t_cw *} cw - Main structure for corewar.
** {int} dump_arg - Index of argument containing the dump_cycle.
** ----------------------------------------------------------------------------
*/

static void			parse_dump_number(t_cw *cw, int dump_arg)
{
	if (dump_arg < cw->parsing.ac)
	{
		FLAG |= FL_DUMP;
		DUMP_CYCLE = ft_stoi(cw->parsing.av[dump_arg]);
	}
	else
		send_error("Missing dump cycle number.\n");
}

/*
** ----------------------------------------------------------------------------
** Function that handles the '-n' flag and assigns a fixed prog_number to
** a champion and verifies that the number given is valid.
**
** {t_cw *} cw - Main structure for corewar.
** {int} num - 	Index of argument containing the requested prog_number for
				next loaded champion.
** {int} champ_arg - Index of argument the champion to be loaded next.
** ----------------------------------------------------------------------------
*/

static void			parse_prog_number(t_cw *cw, int num, int champ_arg)
{
	int		prog_num;

	if (num < cw->parsing.ac)
	{
		prog_num = ft_stoi(cw->parsing.av[num]);
		if ((prog_num - 1) >= MAX_PLAYERS || (prog_num - 1) < 0)
			send_error("Assigning program number must be between 1 and MAX_PLAYERS.\n");
		if (cw->champions[prog_num - 1].manual_assign == 1)
			send_error("Player has already been assigned to this number.\n");
		cw->champions[prog_num - 1].manual_assign = 1;
		champ_load(cw, cw->parsing.av[champ_arg], prog_num - 1);
	}
	else
		send_error("Missing program number.\n");
}

/*
** ----------------------------------------------------------------------------
** Parse the potential flag (arg starting with '-'), check its validity
** and apply it if valid.
**
** {t_cw *} cw - Main structure for corewar.
** {int *} curr_arg - Pointer to index of flag to be analysed (av[curr_arg]).
** ----------------------------------------------------------------------------
*/

static void        parse_flag(t_cw *cw, int *curr_arg)
{
	if (ft_strlen(cw->parsing.av[*curr_arg]) != 2)
		send_error("Incorrect flag.\n");
	cw->parsing.av[*curr_arg]++;
	if (*cw->parsing.av[*curr_arg] == 'd')
		parse_dump_number(cw, ++(*curr_arg));
	else if (*cw->parsing.av[*curr_arg] == 'g')
		FLAG |= FL_GUI;
	else if (*cw->parsing.av[*curr_arg] == 'n' && (*curr_arg) + 2 < cw->parsing.ac)
		parse_prog_number(cw, ++(*curr_arg), ++(*curr_arg));
	else
		send_error("Incorrect flag.\n");
}

/*
** ----------------------------------------------------------------------------
** Main command line parsing function that will parse command line and check
** for any potential errors that might lead to uncatched errors and stores
** all important informations.
**
** {t_cw *} cw - Main structure for corewar.
** ----------------------------------------------------------------------------
*/

void			corewar_parser(t_cw *cw)
{
	int32_t		i;
	static int	champ_num = 0;

	i = -1;
	while (++i < cw->parsing.ac)
	{
		if (cw->parsing.av[i][0] == '-')
			parse_flag(cw, &i);
		else
		{
			champ_load(cw, cw->parsing.av[i], champ_num);
			champ_num++;
		}
	}
	champ_assign(cw);
}