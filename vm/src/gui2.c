/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:28:10 by anjansse          #+#    #+#             */
/*   Updated: 2019/11/13 13:39:11 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


void				print_gui_title(t_cw *cw, t_gui *gui)
{
	(void)cw;
	wattron(gui->win_title, A_BOLD);
	mvwprintw(gui->win_title, 1, 60, "  /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$ /$$      /$$  /$$$$$$  /$$$$$$$ ");
	mvwprintw(gui->win_title, 2, 60, " /$$__  $$ /$$__  $$| $$__  $$| $$_____/| $$  /$ | $$ /$$__  $$| $$__  $$");
	mvwprintw(gui->win_title, 3, 60, "| $$  \\__/| $$  \\ $$| $$  \\ $$| $$      | $$ /$$$| $$| $$  \\ $$| $$  \\ $$");
	mvwprintw(gui->win_title, 4, 60, "| $$      | $$  | $$| $$$$$$$/| $$$$$   | $$/$$ $$ $$| $$$$$$$$| $$$$$$$/");
	mvwprintw(gui->win_title, 5, 60, "| $$      | $$  | $$| $$__  $$| $$__/   | $$$$_  $$$$| $$__  $$| $$__  $$");
	mvwprintw(gui->win_title, 6, 60, "| $$    $$| $$  | $$| $$  \\ $$| $$      | $$$/ \\  $$$| $$  | $$| $$  \\ $$");
	mvwprintw(gui->win_title, 7, 60, "|  $$$$$$/|  $$$$$$/| $$  | $$| $$$$$$$$| $$/   \\  $$| $$  | $$| $$  | $$");
	mvwprintw(gui->win_title, 8, 60, " \\______/  \\______/ |__/  |__/|________/|__/     \\__/|__/  |__/|__/  |__/");
	wattroff(gui->win_title, A_BOLD);
}

void				memory_gui_update(t_cw *cw, t_gui *gui)
{
	int		ixy[3];

	ixy[0] = 0;
	ixy[1] = -2;
	ixy[2] = 1;
	while (ixy[0] < MEM_SIZE)
	{
		if (ixy[1] == MAX_X - 2)
		{
			ixy[1] = -2;
			++ixy[2];
		}
		ixy[1] += 3;
		if (cw->owner[ixy[0]] != -1)
		{
			init_pair(cw->owner[ixy[0]] + 2,
			get_color(cw->owner[ixy[0]]), COLOR_BLACK);
			wattron(gui->win, COLOR_PAIR(cw->owner[ixy[0]] + 2));
			mvwprintw(gui->win, ixy[2], ixy[1], "%02x", cw->memory[ixy[0]]);
			pc_highlight(cw, gui, ixy);
			wattroff(gui->win, COLOR_PAIR(cw->owner[ixy[0]] + 2));
		}
		else if (cw->owner[ixy[0]] == -1)
			mvwprintw(gui->win, ixy[2], ixy[1], "00");
		++ixy[0];
	}
}

int					get_color(char n)
{
	if (n == 0)
		return (COLOR_GREEN);
	else if (n == 1)
		return (COLOR_YELLOW);
	else if (n == 2)
		return (COLOR_RED);
	else if (n == 3)
		return (COLOR_MAGENTA);
	return (0);
}

void				pc_highlight(t_cw *cw, t_gui *gui, int ixy[3])
{
	t_process		*cp;

	cp = cw->process_list;
	while (cp)
	{
		if (ixy[0] == cp->pc)
		{
			init_pair(15, COLOR_BLACK, COLOR_WHITE);
			wattron(gui->win, COLOR_PAIR(15));
			mvwprintw(gui->win, ixy[2], ixy[1], "%02x", cw->memory[cp->pc]);
			wattroff(gui->win, COLOR_PAIR(15));
		}
		cp = cp->next;
	}
}

void				pause_game(t_cw *cw, t_gui *gui, WINDOW *win)
{
	int		key;

	while (1)
	{
		key = wgetch(win);
		if (key == SPACE)
			return ;
		else if (key == ESC)
		{
			endwin();
			exit(0);
		}
		else if (key == KEY_LEFT)
			SPEED = (SPEED >= MIN_SPEED) ? MAX_SPEED : SPEED * 10;
		else if (key == KEY_RIGHT)
			SPEED = (SPEED <= MAX_SPEED) ? MIN_SPEED : SPEED / 10;
		else if (key == KEY_D)
			dump_memory(cw);
		print_gui_info(cw, &cw->gui);
	}
}
