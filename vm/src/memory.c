/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 20:01:05 by qpeng             #+#    #+#             */
/*   Updated: 2019/09/22 17:45:47 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** -----------------------------------------------------------------------------
** Dumps memory to STDOUT at n cycle if requested.
**
** @param {t_vm} vm - current vm structure
** -----------------------------------------------------------------------------
*/

void           memory_dump(t_vm *vm)
{
	int                 i;
	unsigned            siz;

	i = 0;
	siz = (unsigned)sqrt(MEM_SIZE);
	while (i < MEM_SIZE)
	{
		if (i % siz == 0)
		{
			if (i)
				printf("\n");
			if (i == 0)
				write(1, "0x0000 : ", 9);
			else
				printf("%#06x : ", i);
		}
		h_puthex(vm->memory[i]);
		printf(" ");
		i++;
	}
	write(1, "\n", 1);
}

/*
** -----------------------------------------------------------------------------
** Prints memory to the GUI for each cycle.
**
** @param {t_vm} vm - current vm structure
** @param {t_gui} gui - gui struct that contains all ncurses infos.
** -----------------------------------------------------------------------------
*/

void    memory_gui_update(t_vm *vm, t_gui *gui)
{
	if (vm->flag &= FL_GUI)
	{
		int                 i;
		int                 x;
		int                 y;

		i = 0;
		x = -2;
		y = 1;
		int color[4] = {COLOR_YELLOW, COLOR_GREEN, COLOR_RED, COLOR_MAGENTA};
		while (i < MEM_SIZE)
		{
			if (x == MAX_X - 2)
			{
				x = -2;
				++y;
			}
			x += 3;
			if (vm->owner[i] != 7)
			{
				init_pair(vm->owner[i] + 2, color[vm->owner[i] + 1], COLOR_BLACK);
				wattron(gui->win, COLOR_PAIR(vm->owner[i] + 2));
				mvwprintw(gui->win, y, x, "%02x", vm->memory[i]);
				wattroff(gui->win, COLOR_PAIR(vm->owner[i] + 2));
			}
			++i;
		}
	}
}

/*
** -----------------------------------------------------------------------------
**  check if the pointer exceeds the end of the map
**  if yes, then the exceeded part will be count 
**  from the beginning, therefore making it
**  "cicurlar"
** 
** @param {t_byte} pos - the memory position 
**      that will be evaluated
** -----------------------------------------------------------------------------
*/

 t_byte *mem_pos(t_byte *pos)
{
    if (pos > MAP_END)
        return (MAP_START + (pos - MAP_END));
    return (pos);
}

/*
** -----------------------------------------------------------------------------
**  perform read/write operation to the map
**  the map is circular so if read exceeds the 
**  max size of the map, it will read from the 
**  beginning of the map
** 
**  both dst and src can be either the map 
**  or the buffer, it's just moving data 
**  from one place to the other
** 
** @param {t_mem_op} op - memory operation
** @param {t_byte} dst - destination
** @param {t_byte} src - source 
** @param {uint8_t} cnt - length of the buffer
** 
** -----------------------------------------------------------------------------
*/

void    mem_oper(t_mem_op op, t_byte *dst, t_byte *src, uint8_t cnt)
{
    off_t   offset;

    while (cnt--)
    {
        if (op == READ)
            src =  src + 1 > MAP_END ? MAP_START : src;
        else 
            dst = dst + 1 > MAP_END ? MAP_START : dst;
        if (dst > MAP_START && dst < MAP_END)
        {
            offset = dst - MAP_START;
            *(OWNER_START + offset) = CP->champion->id;
        }
        *dst++ = *src++;
    }
}

/*
** -----------------------------------------------------------------------------
** read arg from the memory and place the result 
**  into the buff
** 
** @param {t_arg} arg - arg structure that contains the 
**      info about each arguments and its type
** @param {int32_t} buff - generic buffer that can 
**      store size of data up to 4 bytes
** @param {t_bool} addressing - whather this 
**      read is in "addressing mode", which means
**      the value read as argument will be intrepreted 
**      as address/meta info and the corresponding 
**      operation will be perform, such as: an extra 
**      read will be performed in case of indirect 
**      type argument, the value of the specific 
**      register will be copied into the buffer in case
**      of register type value
** @param {t_bool} far - whather when calculate 
**      the address will be "% IDX_MOD"
** 
** -----------------------------------------------------------------------------
*/

void    read_arg(t_arg *arg, int32_t *buff, t_bool addressing, t_bool far)
{
    int32_t     tmp;

    *buff = 0;
    tmp = 0;
    if (arg->argvt == INDIRECT_TYPE)
    {
        READ_(arg->argv, &tmp, 2);
        *buff = tmp;
        if (addressing)
            READ_(far ? REL(PC, tmp) : ABS(PC, tmp), buff, 4);
    }
    else if (arg->argvt == DIRECT_TYPE)
    {
        READ_(arg->argv, buff, INSTR[*PC - 1].truncate ? 2 : 4);
    }
    else
    {
        READ_(arg->argv, buff, 1);
        if (addressing)
            *buff = CP->registers[*buff];
    }
}