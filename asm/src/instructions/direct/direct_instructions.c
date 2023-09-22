/*
** EPITECH PROJECT, 2023
** asm
** File description:
** direct_instructions
*/

#include "asm.h"

/**
 * @brief   Save a direct argument type.
 * @details This function saves the T_DIR argument type in the given args array
 *          at the current index pointed to by args_ind. It then increments
 *          the args_ind value to point to the next index.
 * @param   args     The array to store the argument types.
 * @param   args_ind Pointer to the current index in the args array.
 */
void save_direct(args_type_t args[4], int *args_ind)
{
    args[*args_ind] = T_DIR;
    (*args_ind)++;
}

/**
 * @brief   Check if an argument is a direct value.
 * @details This function checks if the argument begins with the DIRECT_CHAR
 *          character, indicating that it is a direct value.
 * @param   is_arg_valid Pointer to a boolean variable indicating if the
 *                       argument is valid.
 * @param   arg          The argument to check.
 * @return  true if the argument is a direct value, false otherwise.
 */
bool is_direct(bool *is_arg_valid, char *arg)
{
    if (arg[0] == DIRECT_CHAR) {
        *is_arg_valid = true;
        return true;
    }
    return false;
}

/**
 * @brief   Try adding a direct value to the instruction.
 * @details This function attempts to add a direct value to the instruction.
 *          If the value is a label, it checks if the label exists in the list
 *          of labels. If the label is not found, it sets the unknown_label
 *          pointer and returns -1. If the value is a valid direct value, it
 *          returns the value.
 * @param   asm_data      The ASM data structure.
 * @param   info          The temporary split information.
 * @param   instruction   The instruction to modify.
 * @param   unknown_label Pointer to store the unknown label if encountered.
 * @return  The direct value if valid, or -1 if it's a label.
 */
int try_adding_direct_value(asm_data_t *asm_data, temp_split_t info,
instruction_t *instruction, char **unknown_label)
{
    int value = 0;
    char endptr = '\0';

    if ((info.str + 1)[0] == ':') {
        if (!ll_find_label(asm_data->labels, info.str + 2)) {
            destructor_instruction(instruction);
            exit_asm_arr(asm_data, "Label not found\n", FAILURE, info.split);
        }
        *unknown_label = my_strdup(info.str + 2);
        return -1;
    }
    value = my_atoi(info.str + 1, &endptr);
    if (endptr != '\0') {
        destructor_instruction(instruction);
        exit_asm_arr(asm_data, "Invalid direct value\n", FAILURE, info.split);
    }
    return value;
}
