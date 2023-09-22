/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** LDI
*/

#include "vm.h"

int ldi_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args)
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
    set_argument_value(&args[2], player, vdata,
        arena->battlefield[(player->pc + (sum % IDX_MOD)) % MEM_SIZE]);
    player->carry =
            arena->battlefield[(player->pc + (sum % IDX_MOD)) % MEM_SIZE] == 0;
    return get_instruction_size(args, op_tab[I_LDI]);
}
