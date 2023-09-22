/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Parse arguments bytes
*/

#include "vm.h"

bool has_mem_bypass(op_t op)
{
    const char *bypass_intructions[] = {"lld", "lldi", "lfork", NULL};

    for (int i = 0; bypass_intructions[i]; i++)
        if (my_strcmp(bypass_intructions[i], op.mnemonique) == 0)
            return true;
    return false;
}

int64_t retrieve_data(const u_int8_t battlefield[MEM_SIZE], size_t start,
size_t size)
{
    int64_t data = 0;

    for (size_t i = 0; i < size; i++)
        data = (data << 8) | battlefield[(start + i) % MEM_SIZE];
    switch (size) {
        case 1:
            return *(int8_t *) &data;
        case 2:
            return *(int16_t *) &data;
        case 4:
            return *(int32_t *) &data;
        default:
            return data;
    }
}

size_t get_argument_size(u_int8_t coding_byte, size_t i,
__attribute__((unused)) bool is_index, instruction_arg_t args[3])
{
    if (((coding_byte >> (6 - (i * 2))) & 0b11) == 0b01) {
        args[i].type = T_REG;
        return 1;
    }
    if (((coding_byte >> (6 - (i * 2))) & 0b11) == 0b10) {
        args[i].type = T_DIR;
        return DIR_SIZE;
    }
    if (((coding_byte >> (6 - (i * 2))) & 0b11) == 0b11) {
        args[i].type = T_IND;
        return IND_SIZE;
    }
    return 0;
}

static void get_arguments(instruction_arg_t args[3], int pc,
    arena_t *arena, op_t op)
{
    u_int8_t coding_byte = arena->battlefield[(pc + 1) % MEM_SIZE];
    bool is_index = has_index(op.mnemonique);

    for (size_t i = 0, start = pc + 2, size; i < 3; i++) {
        size = get_argument_size(coding_byte, i, is_index, args);
        if (is_index) {
        size = size != 1 ? IND_SIZE : 1;
            args[i].type |= T_IDX;
        }
        if (size != 0) {
            args[i].data = retrieve_data(arena->battlefield, start, size);
            start += size;
            args[i].idx_mod = has_mem_bypass(op);
        }
    }
}

void parse_instruction_arguments(instruction_arg_t args[3], op_t op,
    int pc, arena_t *arena)
{
    if (has_coding_byte(op.mnemonique)) {
        get_arguments(args, pc, arena, op);
    } else {
        args[0].type = T_DIR;
        has_index(op.mnemonique) ? args[0].type |= T_IDX : 0;
        args[0].idx_mod = has_mem_bypass(op);
        args[0].data = retrieve_data(arena->battlefield, pc + 1,
            has_index(op.mnemonique) ? IND_SIZE : DIR_SIZE);
    }
}
