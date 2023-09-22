/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Or.
*/

#include "vm.h"

/**
 * @brief   Executes the OR instruction.
 * @details This function executes the OR instruction, which performs a bitwise
 *          OR operation on the values of two arguments and stores the result in
 *          a third argument. The function performs validity checks on the
 *          registers specified in the arguments, retrieves their values,
 *          performs the bitwise OR operation, and stores the result in the
 *          destination register. The carry flag of the process is updated based
 *          on the result.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int or_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t or_value;

    if (!is_valid_reg(&args[0]) || !is_valid_reg(&args[1])
    || !is_valid_reg(&args[2]))
        return 1;
    or_value = get_argument_value(&args[0], player, arena) |
        get_argument_value(&args[1], player, arena);
    set_argument_value(&args[2], player, arena, or_value);
    player->carry = or_value == 0;
    return get_instruction_size(args, op_tab[I_OR]);
}
