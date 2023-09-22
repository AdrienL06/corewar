/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Zjmp
*/

#include "vm.h"

/**
 * @brief   Executes the ZJMP instruction.
 * @details This function executes the ZJMP instruction, which performs an
 *          unconditional jump to a specified memory address if the carry flag
 *          is set. The jump is relative to the current program counter (pc)
 *          and is limited to a certain range defined by IDX_MOD. If the carry
 *          flag is not set, the instruction is skipped. The function retrieves
 *          the jump value from the argument, performs the necessary
 *          calculations, and returns the jump offset or the size of the
 *          instruction depending on the outcome.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The jump offset or the size of the instruction in bytes.
 */
int zjmp_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t zjmp_value;
    bool is_neg = false;

    zjmp_value = get_argument_value(&args[0], player, arena);
    if (zjmp_value < 0) {
        zjmp_value *= -1;
        is_neg = true;
    }
    zjmp_value = zjmp_value % IDX_MOD;
    if (is_neg)
        zjmp_value *= -1;
    if (player->carry)
        return (int) zjmp_value;
    return get_instruction_size(args, op_tab[I_ZJMP]);
}
