/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** STI
*/

#include "vm.h"

/**
 * @brief   Executes the STI instruction.
 * @details This function executes the STI instruction, which stores the value
 *          of a register into a memory location computed from the sum of two
 *          argument values. The function performs validity checks on the
 *          registers specified in the arguments, retrieves their values, and
 *          calculates the memory location. The value of the source register is
 *          then stored in the computed memory location.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int sti_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t arg0;
    int64_t arg1;
    int64_t arg2;
    instruction_arg_t new_arg;

    new_arg.data = 0;
    new_arg.type = T_DIR;
    new_arg.idx_mod = has_index_vm(op_tab[I_STI].mnemonique);
    if (!is_valid_reg(&args[0]) || !is_valid_reg(&args[1]) ||
        !is_valid_reg(&args[2]))
        return 1;
    arg0 = get_argument_value(&args[0], player, arena);
    arg1 = get_argument_value(&args[1], player, arena);
    arg2 = get_argument_value(&args[2], player, arena);
    new_arg.data = arg1 + arg2;
    set_argument_value(&new_arg, player, arena, arg0);
    return get_instruction_size(args, op_tab[I_STI]);
}
