/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** ld instruction
*/

#include "vm.h"

/**
 * @brief   Executes the LD instruction.
 * @details This function executes the LD instruction, which loads a value into
 *          a register. The function performs a validity check on the
 *          destination register, retrieves the value from the source argument,
 *          and stores it in the destination register. The carry flag of the
 *          process is updated based on the value loaded.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int ld_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    if (!is_valid_reg(&args[1]))
        return 1;
    set_argument_value(&args[1], player, arena,
        get_argument_value(&args[0], player, arena));
    player->carry = get_argument_value(&args[0], player, arena) == 0;
    return get_instruction_size(args, op_tab[I_LD]);
}
