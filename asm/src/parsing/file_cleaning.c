/*
** EPITECH PROJECT, 2023
** asm
** File description:
** file_cleaning
*/

#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Trims leading and trailing whitespace characters from a string.
 * @details This function removes leading and trailing spaces and tabs from
 *          the given string, creating a new trimmed string. If the resulting
 *          trimmed string is empty, it returns NULL.
 * @param   str The string to trim.
 * @return  A new dynamically allocated string that is the trimmed version of
 *          the input string, or NULL if the resulting string is empty.
 */
char *trim_string(char *str)
{
    char *new_line = NULL;
    int line_length = my_strlen(str);
    int start_index = 0;
    int end_index = line_length - 1;

    for (int i = start_index; str[i] == ' ' || str[i] == '\t'; i++)
        start_index++;
    for (int i = end_index; i >= 0 && (str[i] == ' ' || str[i] == '\t'); i--)
        end_index--;
    if (end_index == -1)
        return NULL;
    new_line = malloc(sizeof(char) * (end_index - start_index + 2));
    for (int i = start_index; i <= end_index; i++)
        new_line[i - start_index] = str[i];
    new_line[end_index - start_index + 1] = '\0';
    return new_line;
}

/**
 * @brief   Removes the comment from a line of code.
 * @details This function checks the given line for comments and removes them.
 *          It also performs validation to ensure that the number of quotes in
 *          the line is valid. If the number of quotes is invalid, it exits the
 *          program with a failure.
 * @param   asm_data A pointer to the `asm_data_t` structure containing the
 *          program data.
 * @param   line     The line of code to remove the comment from.
 * @return  SUCCESS if the comment is successfully removed, otherwise FAILURE.
 */
static int remove_comment(asm_data_t *asm_data, char *line)
{
    int quotes_nbr = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '"')
            quotes_nbr++;
        if (quotes_nbr > 2)
            exit_asm(asm_data, "Invalid number of quotes in name or comment.\n",
            FAILURE);
        if ((quotes_nbr == 0 || quotes_nbr == 2) && line[i] == COMMENT_CHAR) {
            line[i] = '\0';
            return SUCCESS;
        }
    }
    if (quotes_nbr == 1)
        exit_asm(asm_data, "Invalid number of quotes in name or comment.\n",
        FAILURE);
    return SUCCESS;
}

/**
 * @brief   Removes empty lines from the loaded file.
 * @details This function takes an array of strings representing the loaded
 *          file and removes any empty lines. It creates a new array with the
 *          non-empty lines and updates the size accordingly.
 * @param   file The array of strings representing the loaded file.
 * @return  The new array of strings without empty lines.
 */
static char **remove_empty_lines(char **file)
{
    char **new_loaded_file = NULL;
    int new_loaded_file_size = my_arrlen(file);

    for (int i = 0; file[i]; i++)
        if (does_str_contain_only_chars(file[i], " \t"))
            new_loaded_file_size--;
    new_loaded_file = malloc(sizeof(char *) * (new_loaded_file_size + 1));
    new_loaded_file[new_loaded_file_size] = NULL;
    for (int i = 0, j = 0; file[i]; i++) {
        if (does_str_contain_only_chars(file[i], " \t")) {
            free(file[i]);
            continue;
        }
        new_loaded_file[j] = file[i];
        j++;
    }
    free(file);
    return new_loaded_file;
}

/**
 * @brief   Cleans the loaded file by removing leading/trailing whitespace,
 *          comments, and empty lines.
 * @details This function iterates through the loaded file array and performs
 *          the following operations:
 *          1. Trims leading and trailing whitespace of each line.
 *          2. Removes comments from each line.
 *          3. Removes empty lines from the file.
 *          After the cleaning process, it updates the loaded file array and
 *          the file size in the `asm_data_t` structure.
 * @param   asm_data A pointer to the `asm_data_t` structure containing the
 *          program data.
 */
void clean_loaded_file(asm_data_t *asm_data)
{
    char **file = asm_data->loaded_file;
    char *tmp_line = NULL;

    for (int i = 0; file[i]; i++) {
        tmp_line = trim_string(file[i]);
        if (tmp_line) {
            free(file[i]);
            file[i] = tmp_line;
        }
    }
    for (int i = 0; file[i]; i++)
        remove_comment(asm_data, file[i]);
    asm_data->loaded_file = remove_empty_lines(file);
    asm_data->file_size = my_arrlen(asm_data->loaded_file);
}
