/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Xor.
*/

#include "vm.h"

/**
 * @brief   Executes the XOR instruction.
 * @details This function executes the XOR instruction, which performs a
 *          bitwise XOR operation between the values of the first and second
 *          arguments and stores the result in the third argument. The function
 *          performs validity checks on the registers specified in the
 *          arguments, retrieves their values, performs the XOR operation, and
 *          stores the result in the destination register. The carry flag of the
 *          process is updated based on the result.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int xor_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t xor_value;

    if (!is_valid_reg(&args[0]) || !is_valid_reg(&args[1])
    || !is_valid_reg(&args[2]))
        return 1;
    xor_value = get_argument_value(&args[0], player, arena) ^
                get_argument_value(&args[1], player, arena);
    set_argument_value(&args[2], player, arena, xor_value);
    player->carry = xor_value == 0;
    return get_instruction_size(args, op_tab[I_XOR]);
}
