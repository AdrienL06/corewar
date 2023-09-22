/*
** EPITECH PROJECT, 2023
** asm
** File description:
** pre_parsing
*/

#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Frees the memory allocated for a dynamically allocated array of
 *          strings.
 * @details This function is used to free the memory allocated for a dynamically
 *          allocated array of strings. It iterates through the array and frees
 *          each individual string before freeing the array itself.
 *          The function returns `NULL` after freeing the memory.
 * @param   split The array of strings to be freed.
 * @return  `NULL`.
 */
static char *free_split(char **split)
{
    for (int i = 0; split[i]; i++)
        free(split[i]);
    free(split);
    return NULL;
}

/**
 * @brief   Generates the output file name based on the input file name.
 * @details This function takes an input file name and generates the
 *          corresponding output file name by removing the directory path
 *          (if any) and replacing the file extension with ".cor".
 * @param   filename The input file name.
 * @return  The output file name generated based on the input file name.
 */
char *get_output_file_name(char *filename)
{
    char *result = NULL;
    char **split = str_to_array(filename, "/");
    int split_len = my_arrlen(split);
    int result_len = 0;

    if (!*split)
        return free_split(split);
    result_len = my_strlen(split[split_len - 1]);
    if (split[split_len - 1][result_len - 1] == 's'
        && split[split_len - 1][result_len - 2] == '.')
        split[split_len - 1][result_len - 2] = '\0';
    result = my_mstrcat(split[split_len - 1], ".cor");
    free_split(split);
    return result;
}
