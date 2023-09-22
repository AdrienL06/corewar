/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Sub
*/

#include "vm.h"

/**
 * @brief   Executes the SUB instruction.
 * @details This function executes the SUB instruction, which subtracts the
 *          value of the second argument from the value of the first argument
 *          and stores the result in the third argument. The function performs
 *          validity checks on the registers specified in the arguments,
 *          retrieves their values, performs the subtraction, and stores the
 *          result in the destination register. The carry flag of the process is
 *          updated based on the result.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int sub_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t sub_value;

    if (!is_valid_reg(&args[0]) || !is_valid_reg(&args[1])
    || !is_valid_reg(&args[2]))
        return 1;
    sub_value = get_argument_value(&args[0], player, arena) -
                get_argument_value(&args[1], player, arena);
    set_argument_value(&args[2], player, arena, sub_value);
    player->carry = !player->carry;
    return get_instruction_size(args, op_tab[I_SUB]);
}
