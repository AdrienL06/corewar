/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** lfork
*/

#include "vm.h"

/**
 * @brief   Executes the LFORK instruction.
 * @details This function executes the LFORK instruction, which creates a new
 *          process that is a copy of the current process. The new process is
 *          placed at an offset specified by the argument value relative to the
 *          current program counter (PC) of the parent process. The new process
 *          inherits the carry flag of the parent process.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int lfork_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int arg1 = get_argument_value(&args[0], player, arena);
    int new_pc = player->pc + arg1;

    create_new_fork(player, new_pc);
    return get_instruction_size(args, op_tab[I_LFORK]);
}
