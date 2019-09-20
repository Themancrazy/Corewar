/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:01 by qpeng             #+#    #+#             */
/*   Updated: 2019/09/20 12:27:46 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "vm.h"

t_byte	*g_base;

/*
** Declares a winner.
** @param {t_vm} vm - vm struct
*/

static void			player_winner(t_vm *vm)
{
	int			i;
	uint32_t	winner;
	int			winner_id;
	t_champ		curr_ch;

	i = -1;
	winner = vm->corewar.cycle;
	while (++i < vm->corewar.nplayers)
	{
		curr_ch = vm->corewar.champions[i];
		if (vm->corewar.cycle - curr_ch.last_live < winner)
		{
			winner_id = curr_ch.id;
			winner = vm->corewar.cycle - curr_ch.last_live;
		}
	}
	curr_ch = vm->corewar.champions[winner_id];
	printf("Contestant %d, \"%s\", has won ! All HAIL THE KING!\n", curr_ch.id, curr_ch.name);
}

/*
** Introduce all the players to the arena.
** @param {t_vm} vm - vm struct
*/

static void			player_intro(t_vm *vm)
{
	int		i;
	t_champ	curr_ch;

	i = -1;
	write(1, "Introducing contestants...\n", 27);
	while (++i < vm->corewar.nplayers)
	{
		curr_ch = vm->corewar.champions[i];
		printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",\
		curr_ch.id, curr_ch.prog_size, curr_ch.name, curr_ch.comment);
	}
}

/*
** Removes a process from the list of processes in t_process struct.
** @param {t_vm} vm - vm struct
** @param {int} nprocess - pos of node of the process that needs to be terminated. 
*/

static void			process_kill(t_vm *vm, int nprocess)
{
	int 		i;
	t_process	*kp;
	t_process	*head;

	i = -1;
	kp = vm->process_list;
	head = kp;
	while (++i < nprocess - 1) // special condition for first process ?
		kp = kp->next;
	if (i + 2 > vm->nprocess)
		kp->next = NULL;
	else
		kp = kp->next->next;
	vm->process_list = head;
}

/*
** Checks if each process has indeed made a live call during it's turn.
** if not, calls the "process_kill" function.
** @param {t_vm} vm - vm struct
*/

static void			process_check(t_vm *vm)
{
	int 		i;
	t_process	*cp;

	i = -1;
	cp = vm->process_list;
	while (++i < vm->nprocess)
	{
		printf("pid :%d -> ", cp->pid);
		if (cp->live_call == 0)
			process_kill(vm, i);
		else
			cp->live_call = 0;
		cp = cp->next;
	}
	write(1, "\n", 1);
}

/*
** Check for cycle_to die and decrements it if needed.
** @param {t_vm} vm - vm struct 
*/

static int			cycle_check(t_vm *vm)
{
	if ((vm->corewar.cycle % vm->corewar.kill_cycle) == 0)
	{
		vm->corewar.kill_turn++;
		if (vm->corewar.call_live >= NBR_LIVE || vm->corewar.kill_turn > MAX_CHECKS)
		{
			vm->corewar.kill_cycle -= CYCLE_DELTA;
			vm->corewar.kill_turn = 0;
		}
		process_check(vm);
		vm->corewar.call_live = 0;
	}
	if (vm->corewar.cycle == (uint32_t)vm->corewar.dump_cycle)
	{
		dump_mem(vm);
		exit(0);
	}
	return (0);
}

/*
** run corewar game && initialize GUI if flag (-v | -gui) enabled.
** checks for end of game.
** @param {t_vm} vm - vm struct 
*/

void    cw_run(t_vm *vm)
{
	t_gui       gui;

	gui.speed = 1;
	if (vm->flag &= FL_GUI)
		init_gui(&gui);
	else
		player_intro(vm);
	while (1)
	{
		if (vm->flag & FL_GUI)
			update_gui(vm, &gui);
		vm->corewar.cycle += gui.speed * 2;
		p_process_loop(vm);
		cycle_check(vm);
		if (!vm->nprocess)
			break ;
	}
	if (vm->flag & FL_GUI)
		end_screen();
	else
		player_winner(vm);
	
}

/*
**  read flags and if it's champion file 
**  run loader to load it into corewar
** 
**  @param {t_vm} vm - vm struct 
**  @param {int} ac - number of arguments
**  @param {char **} av - argument vector
*/

void    cw_read_args(t_vm *vm, int ac, char **av)
{
	int     i;

	i = 1;
	while (i < ac)
	{
		loader(vm, av[i]);
		i++;
	}
	if (vm->flag & FL_DUMP && vm->corewar.dump_cycle == -1)
		ERROR(RED BOLD"Error: no dump cycle has been given as arg.\n"RESET);
}

/*
**  clean up stage
**  deallocates all the resouces back
** 
**  @param {t_vm} vm - vm struct 
*/

void    cw_cleanup(t_vm *vm)
{
	(void)vm;
	// t_process *tmp;
	
	// tmp = vm->process_list;
	// while (tmp)
	// {
	//     tmp = tmp->next;
	//     free(tmp);
	// }
}

/*
**  init all the env
**  set g_base as the beginning of memory 
** 
**  @param {t_vm} vm - vm struct 
*/

void    cw_env_init(t_vm *vm)
{
	bzero_(vm, sizeof(t_vm));
	vm->debug_mode = 1;
	vm->corewar.nplayers = 0;
	g_base = vm->memory;
	vm->corewar.dump_cycle = -1;
	MAP_START = vm->memory;
	OWNER_START = vm->owner;
	vm->corewar.kill_cycle = CYCLE_TO_DIE;
	vm->corewar.call_live = 0;
	memset_(OWNER_START, 7, MEM_SIZE);
	setbuf(stdout, NULL);
}

/*
**  start the corewar game, set up (initialize all the envs)
**  read all the args and run processes
** 
**  @param {int} ac - number of arguments
**  @param {char **} av - argument vector
*/

void    cw_start(int ac, char **av)
{
	t_vm vm;
	
	if (ac < 2)
	{
		printf("usage: ./vm <champ1, ...>\n");
		exit(EXIT_SUCCESS);
	}
	cw_env_init(&vm);
	cw_read_args(&vm, ac, av);
	cw_run(&vm);
	cw_cleanup(&vm);
}