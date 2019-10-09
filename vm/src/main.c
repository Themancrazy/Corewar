
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

static void			corewar_env(t_cw *cw)
{
	int 	i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		cw->champions[i].manual_assign = 0;
		cw->champions[i].name = "";
		cw->champions[i].prog_number = -1;
		cw->tmp_champ[i].name = "";
	}
}

static void			corewar(int ac, char **av)
{
	t_cw	cw;

	corewar_env(&cw);
	corewar_parser(&cw, ac, av);
	corewar_run(&cw);
}

int             main(int ac, char **av)
{
	if (ac == 1)
		send_error("usage: ./corewar [-v] [-d <cycle>] [-n <n> champs.cor] champs.cor]\n");
	corewar(--ac, ++av);
	return (0);
}