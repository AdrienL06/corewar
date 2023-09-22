/*
** EPITECH PROJECT, 2023
** asm
** File description:
** register_instructions
*/

#include "asm.h"
/**
 * @brief   Save the register argument type.
 * @details This function saves the register argument type in the array of
 *          argument types and increments the argument index.
 * @param   args     The array of argument types.
 * @param   args_ind Pointer to the argument index.
 */
void save_register(args_type_t args[4], int *args_ind)
{
    args[*args_ind] = T_REG;
    (*args_ind)++;
}

/**
 * @brief   Check if the argument is a register.
 * @details This function checks if the argument starts with 'r', indicating
 *          that it is a register. It updates the flag indicating the validity
 *          of the argument accordingly.
 * @param   is_arg_valid Pointer to the flag indicating the argument validity.
 * @param   arg          The argument to check.
 * @return  `true` if the argument is a register, `false` otherwise.
 */
bool is_register(bool *is_arg_valid, char *arg)
{
    if (arg[0] == 'r') {
        *is_arg_valid = true;
        return true;
    }
    return false;
}

/**
 * @brief   Try adding a register value to the instruction.
 * @details This function attempts to convert the given string to a register
 *          value and adds it to the instruction if it is valid. It checks if
 *          the string represents a valid register number and performs the
 *          necessary validation.
 * @param   asm_data    The ASM data structure.
 * @param   info        The temporary split information.
 * @param   instruction The instruction to which the register value will be
 *                      added.
 * @return  The register value if it is valid.
 */
int try_adding_register_value(asm_data_t *asm_data, temp_split_t info,
instruction_t *instruction)
{
    char endptr = '\0';
    int value = my_atoi(info.str + 1, &endptr);

    if (endptr != '\0' || value < 1 || value > REG_NUMBER) {
        destructor_instruction(instruction);
        exit_asm_arr(asm_data, "Invalid register value\n", FAILURE, info.split);
    }
    return value;
}
