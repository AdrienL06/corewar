/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** loader_utils
*/

#include "vm.h"

/**
 * @brief   Handles the index modifier for an instruction argument.
 * @details This function adjusts the size of the argument based on whether it
 *          has an index modifier. If the size is not 1, it sets the size to
 *          IND_SIZE. It also updates the argument type to include T_IDX.
 * @param   size The pointer to the size of the argument.
 * @param   args The array of instruction_arg_t structures.
 * @param   i    The index of the argument.
 */
static void handle_index(size_t *size, instruction_arg_t args[3], size_t i)
{
    *size = *size != 1 ? IND_SIZE : 1;
    args[i].type |= T_IDX;
}

/**
 * @brief   Retrieves the instruction arguments for an error case.
 * @details This function retrieves the instruction arguments when the
 *          instruction has a coding byte. It processes the coding byte to
 *          determine the argument types and sizes. It performs checks to ensure
 *          the arguments can be read from the battlefield. It assigns the
 *          retrieved data and index modifiers to the corresponding arguments.
 * @param   args        The array of instruction_arg_t structures to fill.
 * @param   file        The cor_file_t structure representing the loaded file.
 * @param   battlefield The battlefield (memory) containing the program
 *                      instructions.
 * @param   op          The op_t structure representing the current instruction.
 * @return  Returns 1 if an error occurred, 0 otherwise.
 */
static int get_arguments_error(instruction_arg_t args[3], cor_file_t *file,
u_int8_t *battlefield, op_t op)
{
    bool is_index = has_index_vm(op.mnemonique);
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

/**
 * @brief   Fills the instruction arguments array for an error case.
 * @details This function fills the instruction arguments array with values
 *          appropriate for an error case. If the instruction has a coding byte,
 *          it calls the get_arguments_error function to retrieve the arguments.
 *          Otherwise, it sets the first argument to T_DIR type and assigns the
 *          data based on the instruction's size and presence of an index
 *          modifier. It performs necessary checks to ensure the arguments can
 *          be read from the battlefield.
 * @param   args        The array of instruction_arg_t structures to fill.
 * @param   op          The op_t structure representing the current instruction.
 * @param   file        The cor_file_t structure representing the loaded file.
 * @param   battlefield The battlefield (memory) containing the program
 *                      instructions.
 * @return  Returns 1 if an error occurred, 0 otherwise.
 */
int fill_instruction_arguments_error(instruction_arg_t args[3], op_t op,
cor_file_t *file, u_int8_t *battlefield)
{
    if (has_coding_byte_vm(op.mnemonique)) {
        if (get_arguments_error(args, file, battlefield, op))
            return 1;
    } else {
        args[0].type = T_DIR;
        has_index_vm(op.mnemonique) ? args[0].type |= T_IDX : 0;
        args[0].idx_mod = has_mem_bypass(op);
        if (!can_be_retrieved(file->size, file->pc + 1,
        (has_index_vm(op.mnemonique) ? IND_SIZE : DIR_SIZE)))
            return display_file_error(file->name, op.mnemonique,
                "'s args can't be read", 1);
        args[0].data = retrieve_data(battlefield, file->pc + 1,
        (has_index_vm(op.mnemonique) ? IND_SIZE : DIR_SIZE));
    }
    return 0;
}

/**
 * @brief   Increments the program counter (pc) based on the instruction size.
 * @details This function increments the program counter (pc) based on the size
 *          of the instruction and its arguments. It calculates the size by
 *          examining the argument types of the instruction and adding the
 *          corresponding sizes. It also accounts for the opcode and the coding
 *          byte if present. Finally, it updates the program counter in the
 *          cor_file_t structure.
 * @param   file The cor_file_t structure representing the loaded file.
 * @param   op   The op_t structure representing the current instruction.
 * @param   args The array of instruction_arg_t structures representing the
 *               instruction arguments.
 * @return  Returns the size of the instruction in bytes.
 */
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
    size += 1 + (has_coding_byte_vm(op.mnemonique) ? 1 : 0);
    file->pc += size;
    return size;
}

/**
 * @brief   Checks the validity of registers in the instruction arguments.
 * @details This function verifies the validity of registers in the instruction
 *          arguments. If an invalid register is found, it displays a file error
 *          message and returns a non-zero value.
 * @param   file The cor_file_t structure representing the loaded file.
 * @param   op   The op_t structure representing the current instruction.
 * @param   args The array of instruction_arg_t structures representing the
 *               instruction arguments.
 * @return  Returns 0 if all registers are valid, otherwise returns a non-zero
 *          value.
 */
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
