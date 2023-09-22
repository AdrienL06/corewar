/*
** EPITECH PROJECT, 2023
** asm
** File description:
** instruction_create
*/

#include "asm.h"

/**
 * @brief   Check the validity of the instruction and its arguments.
 * @details This function verifies if the given instruction and its arguments
 *          are valid according to the operation table. It checks the number of
 *          arguments, their types, and validates each argument individually. If
 *          all arguments are valid, it creates an instruction struct and adds
 *          it to the linked list of instructions.
 * @param   asm_data         The ASM data structure.
 * @param   split            The array of string tokens.
 * @param   instruction_code The instruction code.
 * @param   ind              The starting index of the instruction in the split
 *                           array.
 */
void check_instruction(asm_data_t *asm_data, char **split, int instruction_code,
int ind)
{
    op_t op = op_tab[instruction_code];
    bool is_valid = false;
    args_type_t args[4] = {0};
    int args_ind = 0;

    if (my_arrlen(split) - ind - 1 != op.nbr_args)
        exit_asm_arr(asm_data, "Invalid amount of arguments\n", FAILURE, split);
    for (int i = 0; i < op.nbr_args; i++, is_valid = false) {
        if (T_REG & op.type[i] && is_register(&is_valid, split[(ind + 1) + i]))
            save_register(args, &args_ind);
        if (T_DIR & op.type[i] && is_direct(&is_valid, split[(ind + 1) + i]))
            save_direct(args, &args_ind);
        if (T_IND & op.type[i] && is_indirect(&is_valid, split[(ind + 1) + i]))
            save_indirect(args, &args_ind);
        if (!is_valid)
            exit_asm_arr(asm_data, "Invalid argument type\n", FAILURE, split);
    }
    create_instruction(asm_data, split,
    (temp_instruction_t){op, ind}, args);
}
