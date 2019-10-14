
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 23:26:46 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/01 23:27:12 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			get_nplayers(t_cw *cw)
{
	int i;

	i = -1;
	cw->n_players = 0;
	cw->process_list = NULL;
	cw->cycle.kill_cycle = CYCLE_TO_DIE;
	cw->cycle.cycle = 1;
	cw->parsing.flag = 0;
	while (++i < cw->parsing.ac)
	{
		if (ft_strstr(cw->parsing.av[i], ".cor"))
			cw->n_players++;
	}
	if (cw->n_players > MAX_PLAYERS)
		send_error("Too many champions.\n");
}

static void			corewar_env(t_cw *cw, int ac, char **av)
{
	int 	i;

	i = -1;
	cw->parsing.ac = ac;
	cw->parsing.av = av;
	get_nplayers(cw);
	while (++i < MAX_PLAYERS)
	{
		cw->champions[i].manual_assign = 0;
		cw->champions[i].name = "";
		cw->champions[i].prog_number = -1;
		cw->tmp_champ[i].name = "";
	}
	i = -1;
	while (++i < MEM_SIZE)
	{
		cw->memory[i] = 0;
		cw->owner[i] = 0;
	}
}

static void			corewar(int ac, char **av)
{
	t_cw	cw;

	corewar_env(&cw, ac, av);
	corewar_parser(&cw);
	corewar_run(&cw);
}

int             main(int ac, char **av)
{
	if (ac == 1)
		send_error("usage: ./corewar [-v] [-d <cycle>] [-n <n> champs.cor] champs.cor]\n");
	corewar(--ac, ++av);
	return (0);
}