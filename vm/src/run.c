#include "vm.h"

static void         corewar_end(t_cw *cw)
{
	printf("Champion wins (%d).\n", cw->cycle.kill_cycle);
	exit(0);
}

static void         cycle_check(t_cw *cw)
{
	if (cw->cycle.cycle % cw->cycle.kill_cycle == 0)
	{
		//if decrement
			//cw->cycle.kc_cycle = 0;
		++cw->cycle.kc_check;
		if (cw->cycle.kc_check == MAX_CHECKS)
		{
			cw->cycle.kill_cycle -= CYCLE_DELTA;
			cw->cycle.kc_check = 0;
		}
	}
	if (cw->cycle.kill_cycle <= 0)
		corewar_end(cw);
}

static void	player_intro(t_cw *cw)
{
	int 	i;
	t_champ	cc;

	i = -1;
	write(1, "Introducing contestants...\n", 27);
	while (++i < cw->n_players)
	{
		cc = cw->champions[i];
		printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",\
		cc.prog_number, cc.prog_size, cc.name, cc.comment);
	}
}

static void	dump_memory(t_cw *cw)
{
	if (GUI)
		endwin();
	print_memory(cw);
	exit(1);
}

void        corewar_run(t_cw *cw)
{
	if (GUI)
		gui_init(cw);
	else
		player_intro(cw);
	while (1)
	{
		if (GUI)
			gui_update(cw);
		if (DUMP && cw->cycle.cycle == cw->cycle.dump_cycle)
			dump_memory(cw);
		process_update(cw);
		cycle_check(cw);
		++cw->cycle.cycle;
	}
}