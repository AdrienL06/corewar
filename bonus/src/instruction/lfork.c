/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** lfork
*/

#include "vm.h"

int lfork_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int arg1 = get_argument_value(&args[0], player, arena);
    int new_pc = player->pc + arg1;

    create_new_fork(player, new_pc);
    return get_instruction_size(args, op_tab[I_LFORK]);
}
