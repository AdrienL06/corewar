/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** And.
*/

#include "vm.h"

int and_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t and_value;

    if (!is_valid_reg(&args[0]) || !is_valid_reg(&args[1])
    || !is_valid_reg(&args[2]))
        return 1;
    and_value = get_argument_value(&args[0], player, arena) &
        get_argument_value(&args[1], player, arena);
    set_argument_value(&args[2], player, vdata, and_value);
    player->carry = and_value == 0;
    return get_instruction_size(args, op_tab[I_AND]);
}
