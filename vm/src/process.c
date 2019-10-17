#include "vm.h"

void        process_update(t_cw *cw)
{
	t_process   *cp;
	uint8_t		op;

	cp = cw->process_list;
	while (cp)
	{
		op = *(cp->pc);
		if (cw->cycle.cycle - cp->init_cycle == g_op_tab[op].n_cycle)
			instruction_init(cw, &cp, op - 1);
		cp = cp->next;
	}
}

void        process_init(t_cw *cw, t_champ *id, void *pc)
{
	t_process   *cp;
	t_process   **list;

	list = &cw->process_list;
	if (!(cp = (t_process*)malloc(sizeof(t_process))))
		return ;
	cp->carry = 0;
	cp->pc = pc;
	cp->id = id;
	cp->registers[1] = (uint32_t)(id->prog_number);
	cw->n_process++;
	cp->init_cycle = 1;
	cp->next = *list;
	*list = cp;
}