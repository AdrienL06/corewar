/*
** EPITECH PROJECT, 2023
** asm
** File description:
** instruction_create
*/

#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Check if the mnemonic has an index addressing mode.
 * @details This function checks if the given mnemonic has an index addressing
 *          mode, which includes mnemonics like "zjmp", "ldi", "sti", "fork",
 *          "lldi", and "lfork".
 * @param   mnemonique The mnemonic to check.
 * @return  Returns true if the mnemonic has an index addressing mode, false
 *          otherwise.
 */
bool has_index_asm(const char *mnemonique)
{
    const char *index[] = {"zjmp", "ldi", "sti", "fork", "lldi", "lfork", NULL};

    for (int i = 0; index[i]; i++)
        if (my_strcmp(index[i], mnemonique) == 0)
            return true;
    return false;
}

/**
 * @brief   Create a new instruction and add it to the instruction list.
 * @details This function creates a new instruction based on the given
 *          information and adds it to the instruction list in the asm_data
 *          structure.
 * @param   asm_data Pointer to the asm_data_t structure.
 * @param   split    Array of strings representing the split components of the
 *                   line.
 * @param   info     The temp_instruction_t structure containing opcode
 *                   information.
 * @param   args     Array of args_type_t representing the argument types.
 */
void create_instruction(asm_data_t *asm_data, char **split,
temp_instruction_t info, args_type_t args[4])
{
    instruction_t *new = malloc(sizeof(instruction_t));
    new->instruction_code = info.op.code;
    new->coding_byte = get_coding_byte(info.op, args);
    for (int i = 0; i < 4; i++)
        new->args_type[i] = has_index_asm(info.op.mnemonique) && args[i]
                            & (T_DIR | T_IND) ? T_IDX : args[i];
    for (int i = 0; i < 4; i++)
        new->labels_array[i] = NULL;
    for (int i = 0; i < info.op.nbr_args; i++) {
        (args[i] == T_REG) ? new->args[i] = try_adding_register_value(asm_data,
        (temp_split_t){split[i + info.ind + 1], split}, new) : 0;
        (args[i] == T_DIR) ? new->args[i] = try_adding_direct_value(asm_data,
        (temp_split_t){split[i + info.ind + 1], split}, new,
        &new->labels_array[i]) : 0;
        (args[i] == T_IND) ? new->args[i] = try_adding_indirect_value(asm_data,
        (temp_split_t){split[i + info.ind + 1], split}, new,
        &new->labels_array[i]) : 0;
    }
    set_total_bytes(new, info.op);
    ll_add_to_end(asm_data->instructions, (void*)new, T_INSTRUCTION);
}
