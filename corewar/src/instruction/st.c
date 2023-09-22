/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** St instruction
*/

#include "vm.h"

/**
 * @brief   Executes the ST instruction.
 * @details This function executes the ST instruction, which stores the value of
 *          a register into another register or a memory location. The function
 *          performs validity checks on the registers specified in the
 *          arguments, retrieves the value of the source register, and sets it
 *          in the destination register or memory location.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int st_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    if (!is_valid_reg(&args[0]) || !is_valid_reg(&args[1]))
        return 1;
    set_argument_value(&args[1], player, arena,
                        get_argument_value(&args[0], player, arena));
    return get_instruction_size(args, op_tab[I_ST]);
}
