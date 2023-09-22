/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** All functions the referee checking the state of the game
*/

#include <unistd.h>
#include "../../include/vm.h"

/**
 * @brief   Prints the status of a player in the game.
 * @details This function prints the status of a player in the game. It
 *          displays the player number, player name, and the player status
 *          message. The function uses various write operations to output
 *          the information.
 * @param   player_nb    The player number.
 * @param   player_name  The name of the player.
 * @param   player_status  The status message of the player.
 */
void print_player_status(int player_nb, const char *player_name,
                            const char *player_status)
{
    write(1, "The player ", 11);
    my_put_nbr(player_nb);
    write(1, "(", 1);
    write(1, player_name, my_strlen(player_name));
    write(1, ")", 1);
    write(1, player_status, my_strlen(player_status));
    write(1, ".\n", 2);
}

/**
 * @brief   Counts the number of players alive in the virtual machine game.
 * @details This function counts the number of players that are still alive
 *          in the arena based on the `players_alive` array in the referee
 *          structure. It iterates through the players and increments the
 *          count for each player that is marked as alive.
 * @param   data A pointer to the VM data structure.
 * @return  The number of players alive in the game.
 */
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

/**
 * @brief   Checks the end conditions of the virtual machine game.
 * @details This function checks the end conditions of the game by counting the
 *          number of players alive in the arena. If there is only one player
 *          alive, it declares that player as the winner and prints the
 *          corresponding message. If there are more than one player alive,
 *          the function resets the `last_live_call` field in the referee
 *          structure and returns true to continue the game.
 * @param   data A pointer to the VM data structure.
 * @return  Returns false if there is a winner, true otherwise.
 */
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
        print_player_status(winner + 1, arena->players[winner]->player_name,
            "has won");
        return false;
    } else {
        arena->referee->last_live_call = 0;
        return true;
    }
}

/**
 * @brief   Performs the referee checking in the virtual machine.
 * @details This function checks the status of players in the arena and updates
 *          the `players_alive` array in the referee structure based on whether
 *          they have received a live signal or not. It also resets the
 *          `send_live_sig` flag for players who have received a live signal.
 * @param   data A pointer to the VM data structure.
 * @return  Returns the result of the check_end_conditions() function.
 */
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
