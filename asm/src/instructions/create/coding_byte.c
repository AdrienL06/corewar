/*
** EPITECH PROJECT, 2023
** asm
** File description:
** coding_byte
*/

#include "asm.h"

/**
 * @brief   Check if an instruction has a coding byte.
 * @details This function checks if a given mnemonic instruction requires a
 *          coding byte.
 * @param   mnemonique The mnemonic instruction to check.
 * @return  `true` if the instruction has a coding byte, `false` otherwise.
 */
bool has_coding_byte_asm(const char *mnemonique)
{
    const char *no_coding_byte[] = {"zjmp", "live", "fork", "lfork", NULL};

    for (int i = 0; no_coding_byte[i]; i++)
        if (my_strcmp(no_coding_byte[i], mnemonique) == 0)
            return false;
    return true;
}

/**
 * @brief   Convert a binary string to an integer.
 * @details This function converts a binary string representation to an integer.
 * @param   str  The binary string to convert.
 * @param   size The size of the binary string.
 * @return  The converted integer.
 */
static int str_to_int(char *str, int size)
{
    int resultat = 0;

    for (int i = 0; i < size; i++) {
        resultat <<= 1;
        if (str[i] == '1')
            resultat += 1;
    }
    return resultat;
}

/**
 * @brief   Get the coding byte for an instruction.
 * @details This function generates the coding byte for an instruction based on
 *          the provided opcode and argument types. The coding byte indicates
 *          the addressing modes of the instruction's arguments.
 * @param   op   The opcode structure of the instruction.
 * @param   args An array of argument types for the instruction.
 * @return  The coding byte as an 8-bit signed integer. Returns -1 if the
 *          instruction does not require a coding byte.
 */
int8_t get_coding_byte(op_t op, args_type_t args[4])
{
    char coding_byte[8] = "00000000";

    for (int i = 0, ind = 0; i < 4; i++, ind += 2) {
        if (args[i] == T_REG)
            coding_byte[ind + 1] = '1';
        if (args[i] == T_DIR)
            coding_byte[ind] = '1';
        if (args[i] == T_IND) {
            coding_byte[ind] = '1';
            coding_byte[ind + 1] = '1';
        }
    }
    return has_coding_byte_asm(op.mnemonique) ? str_to_int(coding_byte, 8) : -1;
}
