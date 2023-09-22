/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** loader_utils
*/

#include "vm.h"

static void handle_index(size_t *size, instruction_arg_t args[3], size_t i)
{
    *size = *size != 1 ? IND_SIZE : 1;
    args[i].type |= T_IDX;
}

static int get_arguments_error(instruction_arg_t args[3], cor_file_t *file,
u_int8_t *battlefield, op_t op)
{
    bool is_index = has_index(op.mnemonique);
    u_int8_t coding_byte;

    if (!can_be_retrieved(file->size, file->pc + 1, sizeof(u_int8_t)))
        return display_file_error(file->name, "EOF reached", "", 1);
    coding_byte = battlefield[(file->pc + 1)];
    for (size_t i = 0, start = file->pc + 2, size; i < 3; i++) {
        size = get_argument_size(coding_byte, i, is_index, args);
        (is_index) ? handle_index(&size, args, i) : 0;
        if (size == 0)
            continue;
        if (!can_be_retrieved(file->size, start, size)) {
            return display_file_error(file->name, op.mnemonique,
            "'s args can't be read", 1);
        }
        args[i].data = retrieve_data(battlefield, start, size);
        start += size;
        args[i].idx_mod = has_mem_bypass(op);
    }
    return 0;
}

int fill_instruction_arguments_error(instruction_arg_t args[3], op_t op,
cor_file_t *file, u_int8_t *battlefield)
{
    if (has_coding_byte(op.mnemonique)) {
        if (get_arguments_error(args, file, battlefield, op))
            return 1;
    } else {
        args[0].type = T_DIR;
        has_index(op.mnemonique) ? args[0].type |= T_IDX : 0;
        args[0].idx_mod = has_mem_bypass(op);
        if (!can_be_retrieved(file->size, file->pc + 1,
        (has_index(op.mnemonique) ? IND_SIZE : DIR_SIZE)))
            return display_file_error(file->name, op.mnemonique,
                "'s args can't be read", 1);
        args[0].data = retrieve_data(battlefield, file->pc + 1,
        (has_index(op.mnemonique) ? IND_SIZE : DIR_SIZE));
    }
    return 0;
}

int increment_pc(cor_file_t *file, op_t op, instruction_arg_t args[3])
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
    size += 1 + (has_coding_byte(op.mnemonique) ? 1 : 0);
    file->pc += size;
    return size;
}

int check_registers(cor_file_t *file, op_t op, instruction_arg_t args[3])
{
    for (int i = 0; i < op.nbr_args; i++) {
        if (args[i].type & T_REG && (args[i].data < 1
        || args[i].data > REG_NUMBER))
            return display_file_error(file->name, op.mnemonique,
                " Invalid register", 1);
    }
    return 0;
}
