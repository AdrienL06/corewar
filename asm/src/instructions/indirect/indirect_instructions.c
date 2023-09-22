/*
** EPITECH PROJECT, 2023
** asm
** File description:
** indirect_instructions
*/

#include "asm.h"

/**
 * @brief   Save an indirect argument type.
 * @details This function saves the indirect argument type in the arguments
 *          array.
 * @param   args     The array to store the argument types.
 * @param   args_ind Pointer to the index where the argument type should be
 *                   saved.
 */
void save_indirect(args_type_t args[4], int *args_ind)
{
    args[*args_ind] = T_IND;
    (*args_ind)++;
}

/**
 * @brief   Check if the argument is an indirect value.
 * @details This function checks if the argument represents an indirect value.
 *          It verifies that the argument is not a register or a direct value.
 * @param   is_arg_valid Pointer to a flag indicating the validity of the
 *                       argument.
 * @param   arg          The argument to check.
 * @return  `true` if the argument is an indirect value, `false` otherwise.
 */
bool is_indirect(bool *is_arg_valid, char *arg)
{
    bool _tmp = false;

    if (is_register(&_tmp, arg) || is_direct(&_tmp, arg))
        return false;
    *is_arg_valid = true;
    return true;
}

/**
 * @brief   Try adding an indirect value to the instruction.
 * @details This function attempts to add an indirect value to the instruction
 *          based on the provided information. If the value is a label, it
 *          checks if the label exists in the list of labels. If the label is
 *          not found, it sets the `unknown_label` parameter and returns -1.
 *          If the value is a valid integer, it returns the parsed value.
 *          If the value is invalid, it exits with an error message.
 * @param   asm_data      The assembly data.
 * @param   info          The temporary split information.
 * @param   instruction   Pointer to the instruction.
 * @param   unknown_label Pointer to store an unknown label if encountered.
 * @return  The parsed value if it is a valid integer, or -1 if it is a label
 *          and not found.
 */
int try_adding_indirect_value(asm_data_t *asm_data, temp_split_t info,
instruction_t *instruction, char **unknown_label)
{
    int value = 0;
    char endptr = '\0';

    if ((info.str)[0] == ':') {
        if (!ll_find_label(asm_data->labels, info.str + 1)) {
            destructor_instruction(instruction);
            exit_asm_arr(asm_data, "Label not found\n", FAILURE, info.split);
        }
        *unknown_label = my_strdup(info.str + 1);
        return -1;
    }
    value = my_atoi(info.str, &endptr);
    if (endptr != '\0') {
        destructor_instruction(instruction);
        exit_asm_arr(asm_data, "Invalid indirect value\n", FAILURE, info.split);
    }
    return value;
}
