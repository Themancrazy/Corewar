#include "vm.h"

static void			fill_map(WINDOW *win)
{
    int x;
    int y;
    x = -2;
    y = 1;
    while (y != MAX_Y + 1)
    {
       if (x == MAX_X - 2)
        {
            x = -2;
            y++;
        }
        else {
        x += 3;
        mvwprintw(win, y, x, "00");
        }
    }
}

static WINDOW		*init_screen(WINDOW *win, int max_x, int max_y, int y, int x)
{
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    win = newwin(max_y, max_x, y, x);
    nodelay(win, true);
    init_pair(17, COLOR_WHITE, COLOR_WHITE);
    wattron(win, COLOR_PAIR(17));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(17));
    keypad(win, true);
    if (x == 1)
        fill_map(win);
    return (win);
}

static void             pause_game(t_cw *cw, t_gui *gui, WINDOW *win)
{
    int         key;

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
            gui->speed = (gui->speed >= MIN_SPEED) ? MAX_SPEED : gui->speed * 10;
        else if (key == KEY_RIGHT)
            gui->speed = (gui->speed <= MAX_SPEED) ? MIN_SPEED : gui->speed / 10;
        else if (key == KEY_D)
            dump_memory(cw);
    } 
}

static void				update_screen(t_cw *cw, t_gui *gui, WINDOW *win)
{
    int			key;
    
    clear();
    wrefresh(win);
    key = wgetch(win);
    if (key == ESC)
    {
        endwin();
        exit(0);
    }
    else if (key == KEY_LEFT)
        gui->speed = (gui->speed >= MIN_SPEED) ? MAX_SPEED : gui->speed * 10;
    else if (key == KEY_RIGHT)
        gui->speed = (gui->speed <= MAX_SPEED) ? MIN_SPEED : gui->speed / 10;
    else if (key == KEY_D)
        dump_memory(cw);
    else if (key == SPACE)
        pause_game(cw, gui, win);
    usleep(10 * gui->speed);
}

static void			print_info(t_cw *cw, t_gui *gui)
{
    wrefresh(gui->win_info);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
    wattron(gui->win_info, A_BOLD);
    wattron(gui->win_info, COLOR_PAIR(9));
    mvwprintw(gui->win_info, 1, 1, "Current Cycle: %d", cw->cycle.cycle);
    mvwprintw(gui->win_info, 3, 1, "Speed: %0.1lf", 5.0 - log10(gui->speed));
    mvwprintw(gui->win_info, 5, 1, "Kill cycle: %d", cw->cycle.kill_cycle);
    mvwprintw(gui->win_info, 7, 1, "Current winner: %s", cw->winner->name);
    mvwprintw(gui->win_info, 9, 1, "List of commands:");
    mvwprintw(gui->win_info, 10, 4, "- Right Arrow: Increase speed.");
    mvwprintw(gui->win_info, 11, 4, "- Left Arrow: Decrease speed.");
    mvwprintw(gui->win_info, 12, 4, "- Space: Pause/play VM.");
    mvwprintw(gui->win_info, 13, 4, "- Escape: Quit game.");
    mvwprintw(gui->win_info, 14, 4, "- d key: Quit game and dump memory.");
    wattroff(gui->win_info, COLOR_PAIR(9));
}

static inline void	pc_highlight(t_cw *cw, t_gui *gui, int *color, int i, int x, int y)
{
    t_process *cp;
    cp = cw->process_list;
    while (cp)
    {
        if (i == cp->pc)
        {
            init_pair(15, color[cw->owner[i]], COLOR_WHITE);
            wattron(gui->win, COLOR_PAIR(15));
            mvwprintw(gui->win, y, x, "%02x", cw->memory[cp->pc]);
            wattroff(gui->win, COLOR_PAIR(15));
        }
        cp = cp->next;
    }
}

static void    memory_gui_update(t_cw *cw, t_gui *gui)
{
    int                 i;
    int                 x;
    int                 y;
    int color[4] = {COLOR_YELLOW, COLOR_GREEN, COLOR_RED, COLOR_MAGENTA};

    i = 0;
    x = -2;
    y = 1;
    while (i < MEM_SIZE)
    {
        if (x == MAX_X - 2)
        {
            x = -2;
            ++y;
        }
        x += 3;
        if (cw->owner[i] != -1)
        {
            init_pair(cw->owner[i] + 2, color[cw->owner[i]], COLOR_BLACK);
            wattron(gui->win, COLOR_PAIR(cw->owner[i] + 2));
            mvwprintw(gui->win, y, x, "%02x", cw->memory[i]);
            pc_highlight(cw, gui, color, i, x, y);
            wattroff(gui->win, COLOR_PAIR(cw->owner[i] + 2));
        }
        ++i;
    }
}

void			gui_update(t_cw *cw)
{
    update_screen(cw, &cw->gui, cw->gui.win);
    update_screen(cw, &cw->gui, cw->gui.win_info);
    print_info(cw, &cw->gui);
    memory_gui_update(cw, &cw->gui);
}

void			gui_init(t_cw *cw)
{
    cw->gui.win = init_screen(cw->gui.win, MAX_X + 1, MAX_Y + 2, 1, 1);
    cw->gui.win_info = init_screen(cw->gui.win_info, 45, 16, 1, MAX_X + 2);
    cw->gui.speed = MIN_SPEED / 10;
}
