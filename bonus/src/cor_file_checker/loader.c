/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** loader
*/

#include <stdlib.h>
#include "vm.h"

static void check_all_instructions(vm_data_t *data, cor_file_t *file)
{
    instruction_arg_t args[3] = {0};
    op_t op;

    for (int max = file->size - sizeof(header_t), id = -1; id = -1, max > 0;) {
        if (can_be_retrieved(file->size, file->pc, sizeof(u_int8_t)))
            id = retrieve_data(file->bytes, file->pc, sizeof(u_int8_t));
        op = find_instruction(id);
        if (op.code == 0)
            exit_vm_file(data, file->name, "Unknown instruction");
        if (fill_instruction_arguments_error(args, op, file, file->bytes))
            exit_vm(data, "\n", 84);
        if (check_registers(file, op, args))
            exit_vm(data, "\n", 84);
        max -= increment_pc(file, op, args);
    }
}

static void core_file_check(vm_data_t *data, cor_file_t *file)
{
    int64_t magic = 0;

    if ((unsigned int)file->size < sizeof(header_t))
        exit_vm_file(data, file->name, "Too small");
    magic = retrieve_data(file->bytes, 0, sizeof(int));
    if (magic != COREWAR_EXEC_MAGIC)
        exit_vm_file(data, file->name, "Wrong magic number");
    if (retrieve_data(file->bytes, ((PROG_SIZE_POS) % sizeof(int) == 0)
    ? (PROG_SIZE_POS) : (((PROG_SIZE_POS) / sizeof(int)) + 1) * sizeof(int)
    , sizeof(int)) != (int)(file->size - sizeof(header_t)))
        exit_vm_file(data, file->name, "Wrong program size");
    if (file->size - sizeof(header_t) != 0)
        check_all_instructions(data, file);
}

int cor_file_load(vm_data_t *data, temp_player_t player, FILE *fd)
{
    int file_size = 0;
    u_int8_t tmp_buf;

    for (; fread(&tmp_buf, sizeof(u_int8_t), 1, fd) != 0;)
        file_size++;
    data->cor_files[player.prog_nbr - 1] = malloc(sizeof(cor_file_t));
    data->cor_files[player.prog_nbr - 1]->name = player.filename;
    data->cor_files[player.prog_nbr - 1]->size = file_size;
    data->cor_files[player.prog_nbr - 1]->bytes = malloc(sizeof(u_int8_t)
        * file_size);
    data->cor_files[player.prog_nbr - 1]->pc = sizeof(header_t);
    fseek(fd, 0, SEEK_SET);
    for (int i = 0; fread(&tmp_buf, sizeof(u_int8_t), 1, fd) != 0; i++)
        data->cor_files[player.prog_nbr - 1]->bytes[i] = tmp_buf;
    fclose(fd);
    core_file_check(data, data->cor_files[player.prog_nbr - 1]);
    return player.prog_nbr - 1;
}
