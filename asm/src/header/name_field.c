/*
** EPITECH PROJECT, 2023
** asm
** File description:
** name_field
*/

#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Checks if the name field length exceeds the maximum allowed length.
 * @details This function checks if the length of the trimmed name field exceeds
 *          the maximum allowed length (PROG_NAME_LENGTH). If it exceeds,
 *          it frees the allocated memory and exits with an error message.
 * @param   asm_data      Pointer to the assembly data structure.
 * @param   trimmed_name  Pointer to the trimmed name field.
 * @param   split         Array containing the split name field.
 */
static void check_for_name_field_length(asm_data_t *asm_data,
char *trimmed_name, char **split)
{
    if (my_strlen(trimmed_name) > PROG_NAME_LENGTH) {
        free(trimmed_name - 1);
        exit_asm_arr(asm_data, "Name field too long\n", FAILURE, split);
    }
}

/**
 * @brief   Removes the quotes from the trimmed name field and performs
 *          validations.
 * @details This function removes the surrounding quotes from the trimmed name
 *          field and performs validations to ensure the format is correct. It
 *          updates the trimmed_name pointer accordingly.
 * @param   asm_data     Pointer to the assembly data structure.
 * @param   trimmed_name Pointer to the trimmed name field.
 * @param   split        Array containing the split name field.
 */
static void remove_quotes(asm_data_t *asm_data,
char **trimmed_name, char **split)
{
    if ((*trimmed_name)[0] != '"') {
        free(*trimmed_name);
        exit_asm_arr(asm_data, "Invalid name field\n", FAILURE, split);
    }
    (*trimmed_name)[my_strlen(*trimmed_name) - 1] = '\0';
    *trimmed_name += 1;
}

/**
 * @brief   Fills the name field in the header of the assembly data structure.
 * @details This function extracts the name field from the loaded file and
 *          stores it in the prog_name field of the header. It performs
 *          validations and error handling for invalid or missing name field.
 * @param   asm_data Pointer to the assembly data structure.
 */
void fill_name_field(asm_data_t *asm_data)
{
    char **file = asm_data->loaded_file;
    char **split = NULL;
    char *trimmed_name = NULL;

    if (file[0] && file[0][my_strlen(file[0]) - 1] != '"')
        exit_asm(asm_data, "Invalid name field\n", FAILURE);
    split = (file[0]) ? str_to_array(file[0], " \t") : NULL;
    if (asm_data->file_size < 1 || my_strcmp(split[0], NAME_CMD_STRING))
        exit_asm_arr(asm_data, "Name field not found\n", FAILURE, split);
    trimmed_name = trim_string(file[0] + my_strlen(NAME_CMD_STRING));
    if (!trimmed_name)
        exit_asm_arr(asm_data, "Name field empty\n", FAILURE, split);
    remove_quotes(asm_data, &trimmed_name, split);
    check_for_name_field_length(asm_data, trimmed_name, split);
    for (int i = 0; trimmed_name[i] != '\0'; i++)
        asm_data->file_header->prog_name[i] = trimmed_name[i];
    free_array(split);
    free(trimmed_name - 1);
}
