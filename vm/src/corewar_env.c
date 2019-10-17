#include "vm.h"

/*
** ----------------------------------------------------------------------------
** Initialises virtual memory with 0's ('cw->memory') and the owner memory
** ('cw->owner') with -1's (makes sense if you print owner memory for gui).
**
** {t_cw *} cw - Main structure for corewar.
** ----------------------------------------------------------------------------
*/

static void			env_init_memory(t_cw *cw)
{
	int 	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		cw->memory[i] = 0;
		cw->owner[i] = -1;
	}	
}

/*
** ----------------------------------------------------------------------------
** Initialises all elements for the t_champ structure and get a temporary
** estimation of the number of player given on command line.d
**
** {t_cw *} cw - Main structure for corewar.
** ----------------------------------------------------------------------------
*/

static void			env_init_champ(t_cw *cw)
{
	int		i;

	i = -1;
	cw->n_players = 0;
	while (++i < cw->parsing.ac)
	{
		if (ft_strstr(cw->parsing.av[i], ".cor"))
			cw->n_players++;
	}
	if (cw->n_players > MAX_PLAYERS)
		send_error("Too many champions.\n");
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		cw->champions[i].manual_assign = 0;
		cw->champions[i].name = "";
		cw->champions[i].prog_number = -1;
		cw->tmp_champ[i].name = "";
	}
}

/*
** ----------------------------------------------------------------------------
** Main function: launches the virtual machine bu calling 'corewar' and prints
** usage if no argument are given.
**
** {t_cw *} cw - Main structure for corewar.
** {int} ac - Number of argument written on command line
** {char **} av - Array containing all the arguments written on command line.
** ----------------------------------------------------------------------------
*/

void			corewar_env(t_cw *cw, int ac, char **av)
{
	int 	i;

	i = -1;
	cw->parsing.ac = ac;
	cw->parsing.av = av;
	cw->process_list = NULL;
	cw->cycle.kill_cycle = CYCLE_TO_DIE;
	cw->cycle.cycle = 1;
	cw->parsing.flag = 0;
	env_init_champ(cw);
	env_init_memory(cw);
}