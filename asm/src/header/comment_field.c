/*
** EPITECH PROJECT, 2023
** asm
** File description:
** comment_field
*/

#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Checks if a string is a valid instruction mnemonic.
 * @details This function iterates through the op_tab array and compares the
 *          given string with each mnemonic. If a match is found, it returns
 *          true; otherwise, it returns false.
 * @param   str The string to be checked.
 * @return  Returns true if the string is a valid instruction mnemonic, false
 *          otherwise.
 */
static bool is_instruction(char *str)
{
    for (int i = 0; op_tab[i].code; i++)
        if (my_strcmp(str, op_tab[i].mnemonique) == 0)
            return true;
    return false;
}

/**
 * @brief   Checks the length of the comment field.
 * @details This function checks if the length of the trimmed comment exceeds
 *          the maximum allowed comment length. If it does, it frees the
 *          trimmed_comment and exits the program with a failure message,
 *          along with freeing the split array.
 * @param   asm_data        Pointer to the asm_data_t structure.
 * @param   trimmed_comment The trimmed comment field.
 * @param   split           Split array containing the components of the line.
 */
static void check_comment_field_length(asm_data_t *asm_data,
char *trimmed_comment, char **split)
{
    if (my_strlen(trimmed_comment) > COMMENT_LENGTH) {
        free(trimmed_comment - 1);
        exit_asm_arr(asm_data, "Comment field too long\n", FAILURE, split);
    }
}

/**
 * @brief   Handles the special case where no comment field is found.
 * @details This function is called when either the file size is less than 2 or
 *          the first component of the split array does not match the comment
 *          command string. It checks if the split array is NULL or if the first
 *          component is an instruction, and if so, it writes a warning message.
 *          It then frees the split array.
 * @param   split   Split array containing the components of the line.
 */
static void special_case_handling(char **split)
{
    if (!split || is_instruction(split[0]))
        WARNING_WRITE("No comment field found\n", 23);
    free_array(split);
}

/**
 * @brief   Removes the quotes from the trimmed comment field.
 * @details This function checks if the trimmed comment field starts with a
 *          double quote. If not, it exits with an error message. It removes
 *          the quotes from the trimmed comment field by modifying the string
 *          and updates the pointer.
 * @param   asm_data           Pointer to the assembly data structure.
 * @param   trimmed_comment    Pointer to the trimmed comment field string.
 * @param   split              Split array containing the comment field
 *                             components.
 */
static void remove_quotes(asm_data_t *asm_data,
char **trimmed_comment, char **split)
{
    if ((*trimmed_comment)[0] != '"') {
        free(*trimmed_comment);
        exit_asm_arr(asm_data, "Invalid comment field\n", FAILURE, split);
    }
    (*trimmed_comment)[my_strlen(*trimmed_comment) - 1] = '\0';
    *trimmed_comment += 1;
}

/**
 * @brief   Fills the comment field in the file header.
 * @details This function extracts the comment field from the loaded file and
 *          fills it in the file header of the assembly data. It trims the
 *          comment, removes the quotes, and checks for the comment field
 *          length. If any errors are encountered, it exits with an error
 *          message.
 * @param   asm_data      Pointer to the assembly data structure.
 */
void fill_comment_filed(asm_data_t *asm_data)
{
    char **file = asm_data->loaded_file;
    char **split = NULL;
    char *trimmed_comment = NULL;

    split = (asm_data->file_size >= 2)
            ? str_to_array(file[1], " \t") : NULL;
    if (asm_data->file_size < 2 || my_strcmp(split[0], COMMENT_CMD_STRING))
        return special_case_handling(split);
    if (file[1][my_strlen(file[1]) - 1] != '"')
        exit_asm_arr(asm_data, "Invalid comment field\n", FAILURE, split);
    trimmed_comment = trim_string(file[1] + my_strlen(COMMENT_CMD_STRING));
    if (!trimmed_comment)
        exit_asm_arr(asm_data, "Comment field empty\n", FAILURE, split);
    remove_quotes(asm_data, &trimmed_comment, split);
    check_comment_field_length(asm_data, trimmed_comment, split);
    for (int i = 0; trimmed_comment[i] != '\0'; i++)
        asm_data->file_header->comment[i] = trimmed_comment[i];
    free_array(split);
    free(trimmed_comment - 1);
    asm_data->has_comment = true;
}
