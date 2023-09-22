/*
** EPITECH PROJECT, 2023
** asm
** File description:
** free_handling
*/

#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Frees the memory allocated for a dynamically allocated array of
 *          strings.
 * @details This function is used to free the memory allocated for a
 *          dynamically allocated array of strings. It iterates through the
 *          array and frees each individual string before freeing the array
 *          itself.
 * @param   array The array of strings to be freed.
 */
void free_array(char **array)
{
    for (int i = 0; array && array[i]; i++)
        free(array[i]);
    free(array);
}

/**
 * @brief   Frees the allocated memory in the `asm_data_t` structure.
 * @details This function is responsible for freeing the dynamically allocated
 *          memory in the `asm_data_t` structure, including the file
 *          descriptors, output file name, loaded file array, file header,
 *          instruction linked list, label linked list, and the structure
 *          itself.
 * @param   asm_data A pointer to the `asm_data_t` structure containing the
 *          program data.
 */
static void free_asm_data(asm_data_t *asm_data)
{
    if (asm_data->fd_input)
        fclose(asm_data->fd_input);
    free(asm_data->output_file_name);
    free_array(asm_data->loaded_file);
    free(asm_data->file_header);
    ll_free(asm_data->instructions);
    ll_free(asm_data->labels);
    free(asm_data);
}

/**
 * @brief   Exits the Corewar program with the specified exit code and
 *          optional error message.
 * @details This function is used to gracefully exit the program. If the exit
 *          code indicates failure, it can also display an error message before
 *          exiting. The function frees the allocated memory in the
 *          `asm_data_t` structure before exiting.
 * @param   asm_data A pointer to the `asm_data_t` structure containing the
 *          program data.
 * @param   message An optional error message to display if the exit code
 *          indicates failure.
 * @param   exit_code The exit code to use when exiting the program.
 */
void exit_asm(asm_data_t *asm_data, const char *message, int exit_code)
{
    if (exit_code == FAILURE) {
        ERROR_WRITE(message, my_strlen(message));
    }
    free_asm_data(asm_data);
    exit(exit_code);
}

/**
 * @brief   Exits the Corewar program with the specified exit code, optional
 *          error message, and frees an array.
 * @details This function is used to gracefully exit the program. It frees the
 *          specified array before calling the `exit_asm` function to handle
 *          the exit process. If the exit code indicates failure, it can also
 *          display an error message before exiting.
 * @param   asm_data A pointer to the `asm_data_t` structure containing the
 *          program data.
 * @param   message An optional error message to display if the exit code
 *          indicates failure.
 * @param   exit_code The exit code to use when exiting the program.
 * @param   array The array to free before exiting the program.
 */
void exit_asm_arr(asm_data_t *asm_data, const char *message, int exit_code,
char **array)
{
    free_array(array);
    exit_asm(asm_data, message, exit_code);
}
