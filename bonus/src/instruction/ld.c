/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** ld instruction
*/

#include "vm.h"

int ld_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    if (!is_valid_reg(&args[1]))
        return 1;
    set_argument_value(&args[1], player, vdata,
        get_argument_value(&args[0], player, arena));
    player->carry = get_argument_value(&args[0], player, arena) == 0;
    return get_instruction_size(args, op_tab[I_LD]);
}
