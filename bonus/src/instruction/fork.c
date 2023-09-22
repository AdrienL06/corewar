/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** fork
*/

#include <stdlib.h>
#include "vm.h"

void create_new_fork(pfork_t *player, int new_pc)
{
    pfork_t *end_of_list = NULL;

    for (end_of_list = player; end_of_list->next;
    end_of_list = end_of_list->next);
    end_of_list->next = malloc(sizeof(pfork_t));
    end_of_list->next->next = NULL;
    end_of_list->next->pc = new_pc;
    end_of_list->next->carry = player->carry;
    end_of_list->next->cooldown = -1;
    for (int i = 0; i < 16; i++)
        end_of_list->next->registers[i] = player->registers[i];
    end_of_list->next->color = player->color;
    end_of_list->next->player_name = player->player_name;
}

int fork_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int arg1 = get_argument_value(&args[0], player, arena);
    int new_pc = player->pc + (arg1 % IDX_MOD);

    create_new_fork(player, new_pc);
    return get_instruction_size(args, op_tab[I_FORK]);
}
