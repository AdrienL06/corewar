/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** instruction_utils
*/

#include "vm.h"

/**
 * @brief   Calculates the size of an instruction.
 * @details This function calculates the size of an instruction based on its
 *          arguments and the operation type. The size includes the opcode, any
 *          necessary additional bytes for arguments, and the coding byte if
 *          applicable.
 * @param   args The arguments of the instruction.
 * @param   op   The operation type of the instruction.
 * @return  The size of the instruction in bytes.
 */
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
    return 1 + (has_coding_byte_vm(op.mnemonique) ? 1 : 0) + size;
}

/**
 * @brief   Checks if an argument is a valid register.
 * @details This function checks if the specified argument represents a valid
 *          register. If the argument's type indicates that it is a register,
 *          the function verifies if the register number falls within the valid
 *          range of register numbers.
 * @param   args The argument to check.
 * @return  true if the argument is a valid register, false otherwise.
 */
bool is_valid_reg(instruction_arg_t *args)
{
    return args->type & T_REG ? args->data >= 1 && args->data <= REG_NUMBER : 1;
}
