/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** aff
*/

#include <unistd.h>
#include "vm.h"

/**
 * @brief   Executes the AFF instruction.
 * @details This function executes the AFF instruction, which retrieves the
 *          value of a register and writes it to the standard output. The
 *          function performs a validity check on the register specified in the
 *          argument, retrieves its value, and writes it to the standard output.
 *          The value is first reduced to the range 0-255 before writing.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int aff_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t aff_value;

    if (!is_valid_reg(&args[0]))
        return 1;
    aff_value = get_argument_value(&args[0], player, arena);
    aff_value %= 256;
    write(1, &aff_value , 1);
    return get_instruction_size(args, op_tab[I_AFF]);
}
