/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Zjmp
*/

#include "vm.h"

int zjmp_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args)
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
