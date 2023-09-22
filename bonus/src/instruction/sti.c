/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** STI
*/

#include "vm.h"

int sti_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t arg0;
    int64_t arg1;
    int64_t arg2;
    instruction_arg_t new_arg = {0, T_DIR,has_index(op_tab[I_STI].mnemonique)};

    if (!is_valid_reg(&args[0]) || !is_valid_reg(&args[1]) ||
        !is_valid_reg(&args[2]))
        return 1;
    arg0 = get_argument_value(&args[0], player, arena);
    arg1 = get_argument_value(&args[1], player, arena);
    arg2 = get_argument_value(&args[2], player, arena);
    new_arg.data = arg1 + arg2;
    set_argument_value(&new_arg, player, vdata, arg0);
    return get_instruction_size(args, op_tab[I_STI]);
}
