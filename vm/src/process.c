/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 23:50:19 by hypark            #+#    #+#             */
/*   Updated: 2019/11/09 00:11:21 by hypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ----------------------------------------------------------------------------
** DESCRITPTION
**
** {t_cw *} cw -
** {t_process *} cp -
** ----------------------------------------------------------------------------
*/

void				process_add(t_cw *cw, t_process *cp)
{
	t_process		*process;

	process = cw->process_list;
	if (process == NULL)
		cw->process_list = cp;
	else
	{
		cp->next = process;
		cw->process_list = cp;
	}
}

/*
** ----------------------------------------------------------------------------
** DESCRITPTION
**
** {t_cw *} cw -
** {t_process *} cp -
** ----------------------------------------------------------------------------
*/

static t_process	*process_kill(t_cw *cw, t_process *cp)
{
	t_process		*pre_node;

	if (cw->process_list == cp)
	{
		cw->process_list = cp->next;
		free(cp);
		return (cw->process_list);
	}
	else
	{
		pre_node = cw->process_list;
		while (pre_node->next != cp)
			pre_node = pre_node->next;
		pre_node->next = cp->next;
		free(cp);
		return (pre_node->next);
	}
}

/*
** ----------------------------------------------------------------------------
** DESCRITPTION
**
** {t_cw *} cw -
** ----------------------------------------------------------------------------
*/

void				process_check_live(t_cw *cw)
{
	t_process		*cp;

	cp = cw->process_list;
	while (cp)
	{
		if ((cp->live_call >= (CYCLE - KILL_CYCLE)) == 0)
			cp = process_kill(cw, cp);
		else
			cp = cp->next;
	}
	if (cw->process_list == NULL)
		corewar_end(cw);
}

/*
** ----------------------------------------------------------------------------
** DESCRITPTION
**
** {t_cw *} cw -
** ----------------------------------------------------------------------------
*/

void				process_update(t_cw *cw)
{
	t_process		*cp;

	cp = cw->process_list;
	while (cp)
	{
		if (cp->op <= 16 && cp->op >= 0)
		{
			if (CYCLE - cp->init_cycle == g_op_tab[cp->op].n_cycle)
				instruction_proceed(cw, cp);
		}
		else
		{
			cp->pc = (cp->pc + 1) % MEM_SIZE;
			cp->op = cw->memory[cp->pc] - 1;
			cp->init_cycle = CYCLE;
		}
		cp = cp->next;
	}
}

/*
** ----------------------------------------------------------------------------
** DESCRITPTION
**
** {t_cw *} cw -
** {t_champ *} id -
** {uint16_t} pc -
** ----------------------------------------------------------------------------
*/

t_process			*process_init(t_cw *cw, t_champ *id, uint16_t pc)
{
	t_process		*cp;

	if (!(cp = (t_process*)ft_memalloc(sizeof(t_process))))
		send_error("Error occured at process initializing\n");
	cp->pc = pc;
	cp->op = cw->memory[pc] - 1;
	cp->id = id;
	cp->registers[1] = (uint32_t)(id->prog_number * -1);
	cp->process_number = cw->process_index;
	cw->process_index++;
	cp->init_cycle = 0;
	cp->next = NULL;
	return (cp);
}
