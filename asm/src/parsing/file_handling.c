/*
** EPITECH PROJECT, 2023
** asm
** File description:
** file_handling
*/

#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Creates a copy of a line by allocating memory and copying its
 *          contents.
 * @details This function creates a new string by allocating memory and
 *          copying the contents of the specified line. It ensures that the
 *          copied string is null-terminated.
 * @param   line A pointer to the original line string.
 * @param   size The size of the original line string.
 * @return  A pointer to the newly allocated and copied string.
 */
static char *copy_line(char *line, int size)
{
    char *result = malloc(sizeof(char) * (size + 1));

    for (int i = 0; i < size; i++)
        result[i] = line[i];
    result[size] = '\0';
    return result;
}

/**
 * @brief   Loads the content of the input file into an array of strings.
 * @details This function reads the input file line by line using `getline`
 *          and stores each line as a separate string in an array.
 *          It dynamically allocates memory for the array and the strings.
 * @param   asm_data A pointer to the `asm_data_t` structure containing the
 *          program data.
 * @return  An array of strings containing the lines of the input file.
 *          The last element of the array is set to NULL.
 */
char **load_file(asm_data_t *asm_data)
{
    char *lineptr = NULL;
    size_t n = 0;
    int read_bytes = 0;
    char **result = NULL;
    int result_size = 0;

    for (; (read_bytes = getline(&lineptr, &n, asm_data->fd_input)) != EOF;) {
        lineptr[read_bytes - 1] == '\n' ? lineptr[read_bytes - 1] = '\0' : 0;
        result = realloc(result, sizeof(char*) * (result_size + 2));
        result[result_size++] = copy_line(lineptr, read_bytes);
    }
    free(lineptr);
    if (!result)
        exit_asm(asm_data, "File is empty!\n", FAILURE);
    result[result_size] = NULL;
    return result;
}

/**
 * @brief   Checks the input and output files in the Corewar program.
 * @details This function checks the type of command-line arguments, opens
 *          the input file for reading, and retrieves the output file name
 *          from the input file name.
 * @param   asm_data A pointer to the `asm_data_t` structure containing
 *          the program data.
 * @param   ac The number of command-line arguments.
 * @param   av An array of strings containing the command-line arguments.
 */
void check_input_and_output_files(asm_data_t *asm_data, int ac, char **av)
{
    check_arguments_type(asm_data, ac, av);
    asm_data->fd_input = fopen(av[1], "r");
    if (!asm_data->fd_input)
        exit_asm(asm_data, "File doesn't exists!\n", FAILURE);
    asm_data->output_file_name = get_output_file_name(av[1]);
}
