/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** LLDI
*/

#include "vm.h"

/**
 * @brief   Executes the LLDI instruction.
 * @details This function executes the LLDI instruction, which loads a value
 *          from memory into a register with an offset. The function performs
 *          validity checks on the destination register, retrieves the values
 *          from memory and the offset, computes the sum, and stores the result
 *          in the register. The carry flag of the process is updated based on
 *          the loaded value.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int lldi_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t arg0;
    int64_t arg1;
    int64_t sum;

    if (!is_valid_reg(&args[0]) || !is_valid_reg(&args[1]) ||
        !is_valid_reg(&args[2]))
        return 1;
    arg0 = get_argument_value(&args[0], player, arena);
    arg1 = get_argument_value(&args[1], player, arena);
    sum = arg0 + arg1;
    set_argument_value(&args[2], player, arena,
        arena->battlefield[(player->pc + sum) % MEM_SIZE]);
    player->carry = arena->battlefield[(player->pc + sum) % MEM_SIZE] == 0;
    return get_instruction_size(args, op_tab[I_LLDI]);
}
