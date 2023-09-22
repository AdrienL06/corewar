/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Live
*/

#include "vm.h"

/**
 * @brief   Executes the LIVE instruction.
 * @details This function executes the LIVE instruction, which signals that a
 *          player is alive. The function retrieves the value of the argument,
 *          checks if it corresponds to a valid player ID, and updates the
 *          necessary information in the arena and referee. It also prints a
 *          message indicating that the player is alive.
 * @param   arena   The arena containing the battlefield and players.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int live_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t live_value = get_argument_value(&args[0], player, arena);

    if (live_value < 1 || live_value > MAX_PLAYERS)
        return 1;
    if (arena->players[live_value - 1] == NULL)
        return 1;
    print_player_status((int) live_value, player->player_name, "is alive");
    arena->players[live_value - 1]->send_live_sig = true;
    arena->referee->nb_of_live_call++;
    arena->referee->last_live_call = (int) live_value;
    return get_instruction_size(args, op_tab[I_LIVE]);
}
