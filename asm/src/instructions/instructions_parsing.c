/*
** EPITECH PROJECT, 2023
** asm
** File description:
** instructions_parsing
*/

#include <stdlib.h>
#include <stdbool.h>
#include "asm.h"
#include "linked_list.h"

/**
 * @brief   Get the instruction code for the given mnemonic.
 * @details This function searches the operation table for the given mnemonic
 *          and returns the corresponding instruction code. If the mnemonic is
 *          not found, it returns -1.
 * @param   str The mnemonic string to search for.
 * @return  The instruction code if found, otherwise -1.
 */
static int get_instruction(char *str)
{
    for (int i = 0; op_tab[i].code; i++)
        if (my_strcmp(str, op_tab[i].mnemonique) == 0)
            return i;
    return -1;
}

/**
 * @brief   Searches a line for a label and adds it to the label list if valid.
 * @details This function searches a line in the loaded file for a label,
 *          validates the label name, and adds it to the label list if valid.
 *          It also updates the instruction number if the label is followed by
 *          an instruction. It returns true if a valid label is found and added,
 *           otherwise false.
 * @param   asm_data        The assembler data structure.
 * @param   i               The index of the line to search.
 * @param   instruction_nbr Pointer to the current instruction number.
 * @return  True if a valid label is found and added, otherwise false.
 */
bool search_line_for_label(asm_data_t *asm_data, int i, int *instruction_nbr)
{
    char **split = NULL;

    split = str_to_array(asm_data->loaded_file[i],
    (char[]){SEPARATOR_CHAR, ' ', '\t', '\0'});
    if (split[0][my_strlen(split[0]) - 1] == ':'
    && !does_str_contain_only_chars(split[0], ":")) {
        if (is_valid_label(split[0])) {
            try_add_label(asm_data, split, *instruction_nbr);
            (split[1]) ? *instruction_nbr += 1 : 0;
            free_array(split);
            return true;
        } else
            exit_asm_arr(asm_data, "Invalid label name\n", FAILURE, split);
    }
    free_array(split);
    return false;
}

/**
 * @brief   Searches a line for an instruction and processes it.
 * @details This function searches a line in the loaded file for an instruction,
 *          processes it, and performs necessary checks. It assumes that the
 *          line is not empty. It uses the specified instruction code to
 *          validate the instruction and checks for any arguments. It updates
 *          the assembler data accordingly.
 * @param   asm_data The assembler data structure.
 * @param   i        The index of the line to process.
 */
void search_line_for_instruction(asm_data_t *asm_data, int i)
{
    char **split = NULL;
    int instruction_code = -1;
    int start_index = 0;

    split = str_to_array(asm_data->loaded_file[i],
    (char[]){SEPARATOR_CHAR, ' ', '\t', '\0'});
    if (split[0][my_strlen(split[0]) - 1] == ':'
    && !does_str_contain_only_chars(split[0], ":"))
        start_index = 1;
    if (!split[start_index]) {
        free_array(split);
        return;
    }
    instruction_code = get_instruction(split[start_index]);
    if (instruction_code == -1)
        exit_asm_arr(asm_data, "Invalid instruction\n", FAILURE, split);
    check_instruction(asm_data, split, instruction_code, start_index);
    free_array(split);
}

/**
 * @brief   Fills the instructions field in the assembler data.
 * @details This function fills the instructions field in the assembler data by
 *          searching for labels and instructions in the loaded file. It updates
 *          the label positions, assigns labels to instructions, and calculates
 *          the program size. It assumes that the loaded file has at least 2
 *          lines.
 * @param   asm_data The assembler data structure.
 */
void fill_instructions_field(asm_data_t *asm_data)
{
    if (asm_data->file_size < 2)
        return;
    for (int i = (asm_data->has_comment) ? 2 : 1; asm_data->loaded_file[i]; i++)
        if (!search_line_for_label(asm_data, i, &asm_data->tot_instr_nbr))
            asm_data->tot_instr_nbr++;
    for (int i = (asm_data->has_comment) ? 2 : 1; asm_data->loaded_file[i]; i++)
        search_line_for_instruction(asm_data, i);
    for (node_t *curr = asm_data->instructions->head; curr; curr = curr->next)
        update_label(asm_data, curr->data, asm_data->labels);
    asm_data->file_header->prog_size = 0;
    asm_data->curr_instr_nbr = 1;
    for (node_t *curr = asm_data->instructions->head; curr; curr = curr->next) {
        assign_labels(asm_data->file_header, curr->data, asm_data->labels);
        asm_data->curr_instr_nbr++;
    }
    asm_data->file_header->prog_size = __builtin_bswap32(
        asm_data->file_header->prog_size);
}
