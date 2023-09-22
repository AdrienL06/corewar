/*
** EPITECH PROJECT, 2023
** asm
** File description:
** header_parsing
*/

#include "asm.h"

/**
 * @brief   Fills the fields of the header in the assembly data structure.
 * @details This function calls the helper functions to fill the name and
 *          comment fields in the header of the assembly data structure.
 * @param   asm_data Pointer to the assembly data structure.
 */
void fill_header_fields(asm_data_t *asm_data)
{
    fill_name_field(asm_data);
    fill_comment_filed(asm_data);
}
