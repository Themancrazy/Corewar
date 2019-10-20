#include "vm.h"

static void			process_kill(t_cw *cw, int kill_node)
{
	int			i;
	t_process	**kp;

	i = -1;
	kp = &(cw->process_list);
	if (kill_node == 0 && cw->n_process <= 1)
		*kp = NULL;
	else if (kill_node == 0 && cw->n_process > 1)
		*kp = (*kp)->next;
	else
	{
		while (++i < kill_node - 1)
			(*kp) = (*kp)->next;
		(*kp)->next = (*kp)->next->next;
	}
	cw->n_process--;
	cw->n_live_call = 0;
}

void			process_check_live(t_cw *cw)
{
	t_process	*cp;
	int			kill_node;

	kill_node = 0;
	cp = cw->process_list;
	if (cp == NULL)
		corewar_end(cw);
	while (cp)
	{
		if (cp->live_call >= (CYCLE - KILL_CYCLE))
			++kill_node;
		else
			process_kill(cw, kill_node);
		cp = cp->next;
	}
}

/*
** ----------------------------------------------------------------------------
** Function used to go through all of the currently running programs, check
** the ones who need to be executed at this cycle and jump their pc to the
** next instruction's opcode in memory.
**
** {t_cw *} cw - Main structure for corewar.
** ----------------------------------------------------------------------------
*/

void        process_update(t_cw *cw)
{
	t_process   *cp;

	cp = cw->process_list;
	while (cp)
	{
		if (cp->op <= REG_NUMBER)
		{
			if (CYCLE - cp->init_cycle == g_op_tab[cp->op].n_cycle)
				instruction_init(cw, cp);
		}
		if (cp)
			cp = cp->next;
	}
}

/*
** ----------------------------------------------------------------------------
** Function used to check all rules for the game to stay active. I'm too lazy to
** list them all.. maybe later.
**
** {t_cw *} cw - Main structure for corewar.
** {t_champ *} id - Champion to whom this new process belongs to.
** {void *} - Pointer to first begining of instruction in memory.
** ----------------------------------------------------------------------------
*/

void        process_init(t_cw *cw, t_champ *id, void *pc)
{
	t_process   *cp;
	t_process   **list;

	list = &cw->process_list;
	if (!(cp = (t_process*)ft_memalloc(sizeof(t_process))))
		return ;
	cp->pc = pc;
	cp->op = *(cp->pc) - 1;
	cp->id = id;
	cp->registers[1] = (uint32_t)(id->prog_number);
	++cw->n_process;
	cp->init_cycle = 1;
	cp->next = *list;
	*list = cp;
}
