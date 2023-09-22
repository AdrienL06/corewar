/*
** EPITECH PROJECT, 2023
** asm
** File description:
** destructors
*/

#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Destructor function for an instruction in the Corewar program.
 * @details This function frees the memory allocated for an instruction,
 * including its labels array, and then frees the memory of the instruction
 * structure itself.
 * @param   data A pointer to the instruction structure to be destroyed.
 */
void destructor_instruction(void *data)
{
    for (int i = 0; i < 4; i++)
        free(((instruction_t*)data)->labels_array[i]);
    free(data);
}

/**
 * @brief   Destructor function for a label in the Corewar program.
 * @details This function frees the memory allocated for a label, including
 *          its name, and then frees the memory of the label structure itself.
 * @param   data A pointer to the label structure to be destroyed.
 */
void destructor_label(void *data)
{
    free(((label_t*)data)->name);
    free(data);
}
