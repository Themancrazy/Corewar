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

void        corewar_run(t_cw *cw)
{
	while (1)
	{
		if (cw->cycle.cycle == cw->cycle.dump_cycle)
		{
			print_memory(cw);
			exit(1);
		}
		process_update(cw);
		cycle_check(cw);
		++cw->cycle.cycle;
	}
}