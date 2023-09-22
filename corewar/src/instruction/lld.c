/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** lld instruction
*/

#include "vm.h"

/**
 * @brief   Executes the LLD instruction.
 * @details This function executes the LLD instruction, which loads a value from
 *          memory into a register. The function performs validity checks on the
 *          destination register, retrieves the value from memory, and stores it
 *          in the register. The carry flag of the process is updated based on
 *          the loaded value.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int lld_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    if (!is_valid_reg(&args[1]))
        return 1;
    set_argument_value(&args[1], player, arena,
        get_argument_value(&args[0], player, arena));
    player->carry = get_argument_value(&args[0], player, arena) == 0;
    return get_instruction_size(args, op_tab[I_LLD]);
}
