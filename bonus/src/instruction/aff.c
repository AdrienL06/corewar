/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** aff
*/

#include <unistd.h>
#include "vm.h"

int aff_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int64_t aff_value;

    if (!is_valid_reg(&args[0]))
        return 1;
    aff_value = get_argument_value(&args[0], player, arena);
    aff_value %= 256;
    //write(1, &aff_value , 1);
    return get_instruction_size(args, op_tab[I_AFF]);
}
