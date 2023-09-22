/*
** EPITECH PROJECT, 2023
** asm
** File description:
** create_cor_file
*/

#include <fcntl.h>
#include <unistd.h>
#include "asm.h"

/**
 * @brief   Writes the given T_DIR or T_IDX argument into the output file in
 *          binary format.
 * @details The function first checks if the opcode associated with the
 *          instruction requires a coding byte. If it does, the function shifts
 *          the argument's value by 16 bits and writes it into the file as a
 *          2-byte value. Otherwise, it writes the argument's value into the
 *          file as a 4-byte value.
 * @param   instruction The instruction containing the argument to be written.
 * @param   i           The index of the T_DIR or T_IDX argument to be written.
 * @param   file        The file descriptor of the output file.
 */
static void write_dir(instruction_t *instruction, int i, int file)
{
    int tmp_value = 0;

    if (has_index_asm(op_tab[instruction->instruction_code - 1].mnemonique)) {
        instruction->args[i] <<= 16;
        tmp_value = __builtin_bswap32(instruction->args[i]);
        write(file, &tmp_value, IND_SIZE);
    } else {
        tmp_value = __builtin_bswap32(instruction->args[i]);
        write(file, &tmp_value, DIR_SIZE);
    }
}

/**
 * @brief   Writes the given argument into the output file in binary format.
 * @details The function writes the argument into the output file according to
 *          its type. For T_REG arguments, it writes a single byte into the
 *          file. For T_DIR and T_IDX arguments, it writes either DIR_SIZE or
 *          IND_SIZE bytes into the file, depending on whether the opcode
 *          requires a coding byte or not. For T_IND arguments, it writes a
 *          2-byte value into the file.
 * @param   instruction The instruction containing the argument to be written.
 * @param   i           The index of the argument to be written.
 * @param   file        The file descriptor of the output file.
 */
static void write_arg(instruction_t *instruction, int i, int file)
{
    int tmp_value = 0;

    if (instruction->args_type[i] == T_REG)
        write(file, &instruction->args[i], sizeof(int8_t));
    if (instruction->args_type[i] == T_DIR)
        write_dir(instruction, i, file);
    if (instruction->args_type[i] == T_IND) {
        tmp_value = __builtin_bswap32(instruction->args[i] << 16);
        write(file, &tmp_value, IND_SIZE);
    }
    if (instruction->args_type[i] == T_IDX) {
        tmp_value = __builtin_bswap32(instruction->args[i] << 16);
        write(file, &tmp_value, IND_SIZE);
    }
}

/**
 * @brief   Writes the instructions and its arguments into the output file in
 *          binary format.
 * @details The function writes the instructions and their arguments in binary
 *          format into the output file. If the opcode requires a coding byte,
 *          the function writes a single byte into the file. Otherwise, it skips
 *          the coding byte and writes the arguments directly into the file.
 * @param   instruction The instruction to be written into the output file.
 * @param   file        The file descriptor of the output file.
 */
static void write_instruction(instruction_t *instruction, int file)
{
    write(file, &instruction->instruction_code, sizeof(int8_t));
    if (instruction->coding_byte != -1)
        write(file, &instruction->coding_byte, sizeof(int8_t));
    for (int i = 0; i < op_tab[instruction->instruction_code - 1].nbr_args; i++)
        write_arg(instruction, i, file);
}

/**
 * @brief   Print the assembled program into the output file.
 * @details The function writes the file header and all instructions into the
 *          output file in binary format. If an unexpected error occurs while
 *          opening or writing to the output file, the function exits the
 *          program with FAILURE status.
 * @param   asm_data The ASM data structure containing the program data.
 */
void print_into_output_file(asm_data_t *asm_data)
{
    int output_file;

    output_file = open(asm_data->output_file_name, O_CREAT | O_RDWR | O_TRUNC,
        0666);
    if (output_file == -1)
        exit_asm(asm_data, "Unexpected error\n", FAILURE);
    write(output_file, asm_data->file_header, sizeof(header_t));
    for (node_t *curr = asm_data->instructions->head; curr; curr = curr->next)
        write_instruction(curr->data, output_file);
    close(output_file);
}
