/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Exec instructions
*/

#include "vm.h"
#include <stdio.h>

op_t find_instruction(u_int8_t byte)
{
    int i = 0;

    for (; op_tab[i].code != 0; i++) {
        if (op_tab[i].code == byte)
            return op_tab[i];
    }
    return op_tab[i];
}

bool exec_instruction(vm_data_t *vdata, pfork_t *player, arena_t *arena)
{
    instruction_arg_t args[3] = {0};
    op_t current_op;

    current_op = find_instruction(arena->battlefield[player->pc % MEM_SIZE]);
    if (current_op.exec) {
        parse_instruction_arguments(args, current_op, player->pc, arena);
        if (check_valid_args(current_op, args) == false) {
            player->pc++;
            return false;
        } else {
            player->pc += current_op.exec(vdata, arena, player, args);
        }
    } else {
        player->pc++;
        return false;
    }
    return true;
}
/*
printf("Executing instruction %s\n", current_op.mnemonique);
printf("At PC %d\n", player->pc);
printf("Args: \n");
for (int i = 0; i < 3; i++)
printf("Arg %d: type %d, data %ld\n", i, args[i].type, args[i].data);
*/
