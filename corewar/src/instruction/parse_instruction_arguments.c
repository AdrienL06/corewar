/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Parse arguments bytes
*/

#include "vm.h"

/**
 * @brief   Checks if an instruction has memory bypass.
 * @details This function checks if the given instruction, specified by its
 *          mnemonic, has memory bypass. Memory bypass means that the
 *          instruction can bypass the memory index limitation.
 * @param   op The instruction structure representing the opcode and mnemonic.
 * @return  true if the instruction has memory bypass, false otherwise.
 */
bool has_mem_bypass(op_t op)
{
    const char *bypass_intructions[] = {"lld", "lldi", "lfork", NULL};

    for (int i = 0; bypass_intructions[i]; i++)
        if (my_strcmp(bypass_intructions[i], op.mnemonique) == 0)
            return true;
    return false;
}

/**
 * @brief   Retrieves data from the battlefield array and converts it to the
 *          appropriate data type.
 * @details This function retrieves data from the battlefield array starting at
 *          the specified position `start`, with the specified `size`. It
 *          converts the retrieved data to the appropriate signed integer type
 *          based on the size and returns the converted value.
 * @param   battlefield The battlefield array containing the program memory.
 * @param   start       The starting position to retrieve the data from.
 * @param   size        The size of the data to retrieve.
 * @return  The retrieved data converted to the appropriate signed integer type.
 */
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

/**
 * @brief   Determines the size of an argument based on the coding byte.
 * @details This function examines the coding byte to determine the size of an
 *          argument at the given position `i`. It sets the argument type in the
 *          corresponding `args` entry and returns the size of the argument.
 * @param   coding_byte The coding byte of the instruction.
 * @param   i           The position of the argument (0, 1, or 2).
 * @param   is_index    Indicates whether the instruction uses index addressing.
 * @param   args        The array containing the instruction arguments.
 * @return  The size of the argument in bytes, or 0 if the size is invalid.
 */
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

/**
 * @brief   Retrieves the arguments of an instruction from the battlefield.
 * @details This function retrieves the arguments of an instruction from the
 *          battlefield based on the coding byte and opcode information. The
 *          retrieved arguments are stored in the `args` array.
 * @param   args        The array to store the retrieved arguments.
 * @param   pc          The program counter (pc) of the executing process.
 * @param   arena       The arena containing the battlefield.
 * @param   op          The opcode information of the instruction.
 */
static void get_arguments(instruction_arg_t args[3], int pc,
    arena_t *arena, op_t op)
{
    u_int8_t coding_byte = arena->battlefield[(pc + 1) % MEM_SIZE];
    bool is_index = has_index_vm(op.mnemonique);

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

/**
 * @brief   Parses the arguments of an instruction.
 * @details This function parses the arguments of an instruction based on the
 *          opcode information. If the instruction has a coding byte, it calls
 *          the `get_arguments` function to retrieve the arguments from the
 *          battlefield. Otherwise, it directly assigns the arguments based on
 *          the opcode information. The parsed arguments are stored in the
 *          `args` array.
 * @param   args    The array to store the parsed arguments.
 * @param   op      The opcode information of the instruction.
 * @param   pc      The program counter (pc) of the executing process.
 * @param   arena   The arena containing the battlefield.
 */
void parse_instruction_arguments(instruction_arg_t args[3], op_t op,
    int pc, arena_t *arena)
{
    if (has_coding_byte_vm(op.mnemonique)) {
        get_arguments(args, pc, arena, op);
    } else {
        args[0].type = T_DIR;
        has_index_vm(op.mnemonique) ? args[0].type |= T_IDX : 0;
        args[0].idx_mod = has_mem_bypass(op);
        args[0].data = retrieve_data(arena->battlefield, pc + 1,
            has_index_vm(op.mnemonique) ? IND_SIZE : DIR_SIZE);
    }
}
