/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:31:59 by qpeng             #+#    #+#             */
/*   Updated: 2019/09/23 11:15:24 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int8_t     *g_ownerbase;

/*
** -----------------------------------------------------------------------------
** Handles dump cycle and number of champion and saves it to vm struct.
**
** @param {t_vm} vm - current vm structure
** @param {char *} arg - argv given.
** -----------------------------------------------------------------------------
*/

static void		handle_dump_num(t_vm *vm, char *arg)
{
	int64_t		n;

	n = ft_atoi(arg);
	if (n < 0)
		ERROR("Number can't be negative.\n");
	if (vm->flag & FL_NUM)
	{
		n = (uint8_t)n;
		if (n > MAX_PLAYERS)
			ERROR("number is too big to be assigned to a player (0 < n < MAX_PLAYERS).\n");
		vm->corewar.next_player_id = n;
	}
	else if (vm->flag & FL_DUMP)
		vm->corewar.dump_cycle = n;
	vm->flag &= 0b00000011;
}

/*
** -----------------------------------------------------------------------------
** Function used to save all flags to vm->flag and check which flag
** has been called at all time.
**
** @param {t_vm} vm - current vm structure
** @param {char *} filename - flag given.
** -----------------------------------------------------------------------------
*/

static void    save_flag(t_vm *vm, char *filename)
{
	if ((!scmp_(filename, "-gui") || !scmp_(filename, "v")) && !(vm->flag & FL_GUI) && !(vm->flag & FL_DUMP))
		vm->flag |= FL_GUI;
	else if ((!scmp_(filename, "d") || !scmp_(filename, "-dump")) && !(vm->flag & FL_DUMP) && !(vm->flag & FL_GUI))
	{
		vm->flag |= FL_DUMP;
		vm->flag |= EXPECT_ARG;
	}
	else if (!scmp_(filename, "n"))
	{
		vm->flag |= FL_NUM;
		vm->flag |= EXPECT_ARG;
	}
	else
		ERROR(RED BOLD"Error: flag invalid.\n"RESET);
}

/*
** -----------------------------------------------------------------------------
** Analyse args given, loads champions, handles flags and returns parsing errors
**
** @param {t_vm} vm - current vm structure
** @param {char *} arg - argv given.
** -----------------------------------------------------------------------------
*/

void    loader(t_vm *vm, char *arg)
{
	int fd;

	if (*arg == '-' && !(vm->flag & EXPECT_ARG))
	{
		save_flag(vm, &(arg[1]));
		return ;
	}
	else if (ft_strstr(arg, ".cor") && !(vm->flag & EXPECT_ARG))
	{
		if ((fd = open(arg, O_RDONLY)) == -1)
			ERROR(RED BOLD"Error: File doesn't exist.\n"RESET); 
		if (vm->corewar.nplayers + 1 > MAX_PLAYERS)
			ERROR(RED BOLD"Error: max number of players reached.\n"RESET);
		++vm->corewar.nplayers;
		ch_load_champ(vm, fd);
	}
	else
	{
		if (sverif_(arg, "0123456789") && vm->flag & EXPECT_ARG)
			handle_dump_num(vm, arg);
		else
			ERROR(RED BOLD"Error\n\n"RESET"usage: ./corewar [-v | --gui] [-d | --dump <cycle>] [[-n <n>] champs.cor]\n");
	}
}