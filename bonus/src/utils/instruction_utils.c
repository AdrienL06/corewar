/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** instruction_utils
*/

#include "vm.h"

int get_instruction_size(instruction_arg_t *args, op_t op)
{
    int size = 0;

    for (int i = 0; i < op.nbr_args; i++) {
        if (args[i].type & T_REG) {
            size += 1;
            continue;
        }
        if (args[i].type & T_IDX) {
            size += IND_SIZE;
            continue;
        }
        if (args[i].type & T_DIR)
            size += DIR_SIZE;
        if (args[i].type & T_IND)
            size += IND_SIZE;
    }
    return 1 + (has_coding_byte(op.mnemonique) ? 1 : 0) + size;
}

bool is_valid_reg(instruction_arg_t *args)
{
    return args->type & T_REG ? args->data >= 1 && args->data <= REG_NUMBER : 1;
}
