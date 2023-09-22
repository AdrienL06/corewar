/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Utils
*/

#include "vm.h"

bool has_coding_byte(const char *mnemonique)
{
    const char *no_coding_byte[] = {"zjmp", "live", "fork", "lfork", NULL};

    for (int i = 0; no_coding_byte[i]; i++)
        if (my_strcmp(no_coding_byte[i], mnemonique) == 0)
            return false;
    return true;
}

bool has_index(const char *mnemonique)
{
    const char *index[] = {"zjmp", "ldi", "sti", "fork", "lldi", "lfork", NULL};

    for (int i = 0; index[i]; i++)
        if (my_strcmp(index[i], mnemonique) == 0)
            return true;
    return false;
}

bool check_valid_args(op_t op, instruction_arg_t *args)
{
    for (int i = 0; i < op.nbr_args; i++)
        if (!(args[i].type & op.type[i]))
            return false;
    return true;
}

int64_t get_argument_value(instruction_arg_t *args, pfork_t *player,
                            arena_t *arena)
{
    if (args->type & T_REG)
        return player->registers[args->data - 1];
    if (args->type & T_DIR)
        return args->data;
    else {
        if (args->idx_mod)
            return arena->battlefield
                [((args->data + player->pc) % IDX_MOD) % MEM_SIZE];
        else
            return arena->battlefield[(args->data + player->pc) % MEM_SIZE];
    }
    return 0;
}

void set_argument_value(instruction_arg_t *args, pfork_t *player,
                        vm_data_t *vdata, reg_t value)
{
    int64_t index = 0;

    if (args->type & T_REG) {
        player->registers[args->data - 1] = value;
        return;
    }
    if (args->idx_mod)
        index = (args->data % IDX_MOD) + player->pc;
    else
        index = args->data + player->pc;
    for (size_t i = 0; i < sizeof(reg_t); i++) {
        vdata->arena->battlefield[(index + i) % MEM_SIZE] =
            (value >> (8 * (sizeof(reg_t) - i - 1))) & 0xFF;
        vdata->arena->nattr[(index + i) % MEM_SIZE] = *player->color;
    }
}
