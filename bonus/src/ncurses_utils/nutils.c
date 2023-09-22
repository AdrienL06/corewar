/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** nutils
*/

#include "vm.h"
#include "bonus.h"

int set_pc_attr(vm_data_t *vdata, int z)
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!vdata->arena->players[i])
            continue;
        for (pfork_t *curr = vdata->arena->players[i]->forks; curr; curr = curr->next) {
            if (curr->pc % MEM_SIZE == z) {
                wattron(vdata->ndata->arena->win, COLOR_PAIR(vdata->arena->players[i]->color) | A_BOLD | A_UNDERLINE | A_REVERSE);
                return i;
            }
        }
    }
    return -1;
}

void display_arena_ncurses(vm_data_t *data, ncurses_data_t *ndata, int start_x)
{
    int x = ndata->arena->x + 1;
    int y = ndata->arena->y + 1;
    int start = start_x * (ndata->arena->width - 2) / 2;

    for (int i = start; i < MEM_SIZE + start; i++) {
        if (i < MEM_SIZE) {
            int player = set_pc_attr(data, i);
            if (player == -1)
                wattron(ndata->arena->win, COLOR_PAIR(data->arena->nattr[i]));
            if (data->arena->battlefield[i] != 0)
                mvwprintw(ndata->arena->win, x, y, "%02X", data->arena->battlefield[i]);
            else
                mvwprintw(ndata->arena->win, x, y, "--");
            wattroff(ndata->arena->win, COLOR_PAIR(data->arena->nattr[i]) | A_BOLD | A_UNDERLINE | A_REVERSE);
            if (player != -1)
                wattroff(ndata->arena->win, COLOR_PAIR(data->arena->players[player]->color) | A_BOLD | A_UNDERLINE | A_REVERSE);
        } else {
            mvwprintw(ndata->arena->win, x, y, "  ");
        }
        y += 2;
        if (y >= ndata->arena->width - 2) {
            y = 1;
            x++;
        }
        if (x >= ndata->arena->height - 1)
            break;
    }
    wrefresh(ndata->arena->win);
}

void display_player_info(vm_data_t *vdata, ncurses_data_t *ndata)
{
    int x = 1, y = 1;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!vdata->arena->players[i])
            continue;
        wattron(ndata->players->win, COLOR_PAIR(vdata->arena->players[i]->color) | A_UNDERLINE);
        mvwprintw(ndata->players->win, x, y, "Player %d:", i + 1);
        wattroff(ndata->players->win, COLOR_PAIR(vdata->arena->players[i]->color) | A_UNDERLINE);
        mvwprintw(ndata->players->win, x, y + 10, " %s", vdata->arena->players[i]->player_name);
        for (int j = 0, print_x = 0, reg = 0; reg < REG_NUMBER; j++, reg++) {
            if (j % 3 == 0) {
                print_x++;
                j = 0;
            }
            mvwprintw(ndata->players->win, x + 1 + print_x, 1 + j * 12, "r%02d %7x", reg + 1, vdata->arena->players[i]->forks->registers[reg]);
        }
        x += 9;
    }
    wrefresh(ndata->players->win);
}