/*
** EPITECH PROJECT, 2023
** asm
** File description:
** total_bytes
*/

#include "asm.h"

/**
 * @brief   Set the total number of bytes for an instruction.
 * @details This function calculates and sets the total number of bytes required
 *          to represent the given instruction. The calculation takes into
 *          account the argument types and sizes specified by the op_t
 *          structure.
 * @param   instruction Pointer to the instruction structure.
 * @param   op          The op_t structure representing the instruction's
 *                      opcode.
 */
void set_total_bytes(instruction_t *instruction, op_t op)
{
    instruction->total_bytes = 1 + (has_coding_byte_asm(op.mnemonique) ? 1 : 0);
    for (int i = 0; i < op.nbr_args; i++) {
        if (instruction->args_type[i] == T_REG)
            instruction->total_bytes += 1;
        if (instruction->args_type[i] == T_DIR)
            instruction->total_bytes += DIR_SIZE;
        if (instruction->args_type[i] == T_IND)
            instruction->total_bytes += IND_SIZE;
        if (instruction->args_type[i] == T_IDX)
            instruction->total_bytes += IND_SIZE;
    }
}
