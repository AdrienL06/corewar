/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** main
*/

#include <unistd.h>
#include <stdlib.h>
#include "vm.h"
#include "bonus.h"

cwindow_t *create_window(int x, int y, int width, int height, int color)
{
    cwindow_t *new = malloc(sizeof(cwindow_t));

    new->win = newwin(height, width, y, x);
    wbkgd(new->win, color);
    box(new->win, 0, 0);
    refresh();
    wrefresh(new->win);
    getmaxyx(new->win, new->height, new->width);
    getbegyx(new->win, new->y, new->x);
    return new;
}

ncurses_data_t *init_ncurses_settings(void)
{
    ncurses_data_t *new = malloc(sizeof(ncurses_data_t));
    my_memset(new, 0, sizeof(ncurses_data_t));

    /* BASIC INITS */
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    curs_set(0);
    set_escdelay(0);

    /* COLORS */
    if (!has_colors()) {
        endwin();
        printf("The terminal doesn't support color\n");
        exit(42);
    }
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(C_MAX, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);

    /* WINDOWS */
    //new->arena = create_window(0, 0, COLS, LINES, COLOR_PAIR(C_MAX));
    new->arena = create_window(0, 0, COLS - PLAYER_WIN_SIZE, LINES, COLOR_PAIR(C_MAX));
    new->players = create_window(COLS - PLAYER_WIN_SIZE, 0, PLAYER_WIN_SIZE, LINES, COLOR_PAIR(C_MAX));
    mvwprintw(new->arena->win, 0, 2, "COREWAR VISUALIZER");
    wrefresh(new->arena->win);

    /* MOUSE */
    mousemask(ALL_MOUSE_EVENTS, NULL);
    
    /* OTHER */
    new->is_running = true;
    new->scroll_pos = 0;
    return new;
}

void exit_ncurses(ncurses_data_t *data)
{
    delwin(data->arena->win);
    delwin(data->players->win);
    free(data->arena);
    free(data->players);
    free(data);
    endwin();
}

int main(int argc, char **argv)
{
    vm_data_t *vdata = init_vm_data();

    parse_arguments(argc, argv, vdata);
    create_arena(vdata);

    ncurses_data_t *ndata = init_ncurses_settings();
    vdata->ndata = ndata;
    check_events(ndata, vdata);
    start_vm(vdata);
    //check_events(ndata, data);
    exit_ncurses(ndata);
    exit_vm(vdata, NULL, SUCCESS);
}
