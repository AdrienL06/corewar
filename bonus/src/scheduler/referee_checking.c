/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** All functions the referee checking the state of the game
*/

#include <unistd.h>
#include "../../include/vm.h"
#include <ncurses.h>

void print_player_status(cwindow_t *players, int player_nb, const char *player_name,
                            const char *player_status)
{
    mvwprintw(players->win, players->height - 2, 1, "The player %d(%s) %s.\n", player_nb, player_name, player_status);
    box(players->win, 0, 0);
    wrefresh(players->win);
    /* write(1, "The player ", 11);
    my_put_nbr(player_nb);
    write(1, "(", 1);
    write(1, player_name, my_strlen(player_name));
    write(1, ")", 1);
    write(1, player_status, my_strlen(player_status));
    write(1, ".\n", 2); */
}

static int count_nb_player_alive(vm_data_t* data)
{
    arena_t *arena = data->arena;
    int players_alive = 0;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (arena->players[i] == NULL)
            continue;
        if (arena->referee->players_alive[i] == true) {
            players_alive++;
        }
    }
    return players_alive;
}

static int check_end_conditions(vm_data_t* data)
{
    arena_t *arena = data->arena;
    int winner = -1;
    int players_alive = count_nb_player_alive(data);

    if (players_alive < 2) {
        for (int i = 0; i < MAX_PLAYERS && winner == -1; i++)
                winner = arena->players[i] != NULL ? i : winner;
        if (arena->referee->last_live_call != 0)
            winner = arena->referee->last_live_call - 1;
        print_player_status(data->ndata->players, winner + 1, arena->players[winner]->player_name,
            "has won");
        int ch = getch();
        while (ch != ' ')
            ch = getch();
        return false;
    } else {
        arena->referee->last_live_call = 0;
        return true;
    }
}

int referee_checking(vm_data_t* data)
{
    arena_t *arena = data->arena;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!arena->players[i])
            continue;
        if (arena->players[i]->send_live_sig == false) {
            arena->referee->players_alive[i] = false;
        } else {
            arena->referee->players_alive[i] = true;
            arena->players[i]->send_live_sig = false;
        }
    }
    return check_end_conditions(data);
}
