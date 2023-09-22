/*
** EPITECH PROJECT, 2023
** asm
** File description:
** init_handling
*/

#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Initializes a new `header_t` structure.
 * @details This function allocates memory for the `header_t` structure,
 *          initializes its members, and returns a pointer to the newly
 *          created structure.
 * @return  A pointer to the newly created `header_t` structure.
 */
static header_t *init_asm_header(void)
{
    header_t *new = malloc(sizeof(header_t));
    my_memset(new, 0, sizeof(header_t));
    new->magic = __builtin_bswap32(COREWAR_EXEC_MAGIC);
    for (int i = 0; i < PROG_NAME_LENGTH + 1; i++)
        new->prog_name[i] = 0;
    for (int i = 0; i < COMMENT_LENGTH + 1; i++)
        new->comment[i] = 0;
    new->prog_size = 0;
    return new;
}

/**
 * @brief   Initializes an array of destructors for the Corewar program.
 * @details This function allocates memory for the `destructor_t` array and
 *          assigns the appropriate destructor functions to each element based
 *          on the corresponding destructor type.
 * @return  A pointer to the array of destructors.
 */
destructor_t *init_asm_destructors(void)
{
    destructor_t *destructors = NULL;

    destructors = malloc(sizeof(destructor_t) * MAX_DESTRUCTOR_NBR);
    destructors[T_NONE] = NULL;
    destructors[T_LABEL] = &destructor_label;
    destructors[T_INSTRUCTION] = &destructor_instruction;
    return destructors;
}

/**
 * @brief   Initializes a new `asm_data_t` structure.
 * @details This function allocates memory for the `asm_data_t` structure,
 *          initializes its members, and returns a pointer to the newly
 *          created structure.
 * @return  A pointer to the newly created `asm_data_t` structure.
 */
asm_data_t *init_asm_data(void)
{
    asm_data_t *new = malloc(sizeof(asm_data_t));
    destructor_t *destructors = init_asm_destructors();
    new->fd_input = NULL;
    new->output_file_name = NULL;
    new->loaded_file = NULL;
    new->file_size = 0;
    new->file_ind = 0;
    new->file_header = init_asm_header();
    new->has_comment = false;
    new->instructions = ll_init(destructors);
    new->labels = ll_init(destructors);
    new->curr_instr_nbr = 0;
    new->tot_instr_nbr = 0;
    free(destructors);
    return new;
}
