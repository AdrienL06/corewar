/*
** EPITECH PROJECT, 2023
** asm
** File description:
** labels_parsing
*/

#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Checks if a character is valid for a label.
 * @details This function checks if a given character is valid for a label by
 *          iterating through the LABEL_CHARS array and comparing each element
 *          with the character.
 * @param   c The character to be checked.
 * @return  Returns true if the character is valid for a label, false otherwise.
 */
static bool is_char_in_label_chars(char c)
{
    for (int i = 0; LABEL_CHARS[i]; i++)
        if (c == LABEL_CHARS[i])
            return true;
    return false;
}

/**
 * @brief   Checks if a label is valid.
 * @details This function checks if a label is valid by iterating through each
 *          character of the label and verifying if it belongs to the set of
 *          valid label characters.
 * @param   label The label to be checked.
 * @return  Returns true if the label is valid, false otherwise.
 */
bool is_valid_label(char *label)
{
    for (int i = 0; i < my_strlen(label) - 1; i++)
        if (!is_char_in_label_chars(label[i]))
            return false;
    return true;
}

/**
 * @brief   Tries to add a label to the label linked list.
 * @details This function attempts to add a label to the label linked list in
 *          the asm_data structure. It checks if the label is already defined
 *          by searching for it in the linked list using ll_find_label. If the
 *          label is found, it exits with an error message. Otherwise, it
 *          creates a new label, assigns its name, integer position, and sets
 *          the byte position to -1. Finally, it adds the label to the end of
 *          the linked list.
 * @param   asm_data        The assembly data structure.
 * @param   split           The array of strings containing the label name.
 * @param   instruction_nbr The current instruction number.
 */
void try_add_label(asm_data_t *asm_data, char **split, int instruction_nbr)
{
    label_t *new = NULL;
    char *new_label = my_strdup(split[0]);
    new_label[my_strlen(new_label) - 1] = '\0';
    if (ll_find_label(asm_data->labels, new_label)) {
        free(new_label);
        exit_asm_arr(asm_data, "Label already defined\n", FAILURE, split);
    }
    new = malloc(sizeof(label_t));
    new->name = new_label;
    new->int_pos = instruction_nbr;
    new->byte_pos = -1;
    ll_add_to_end(asm_data->labels, (void*)new, T_LABEL);
}

/**
 * @brief   Updates the byte positions of labels.
 * @details This function updates the byte positions of labels in the linked
 *          list based on the current program size and the total bytes of the
 *          instruction. It iterates over the linked list of labels and checks
 *          if the label's integer position matches the current instruction
 *          number or the total instruction number. If a match is found, the
 *          label's byte position is updated accordingly. Finally, it updates
 *          the program size in the file header and increments the current
 *          instruction number.
 * @param   asm_data    The assembly data containing the file header, current
 *                      instruction
 *                      number, and total instruction number.
 * @param   instruction The current instruction.
 * @param   labels      The linked list of labels.
 */
void update_label(asm_data_t *asm_data, instruction_t *instruction,
linked_list_t *labels)
{
    for (node_t *curr = labels->head; curr; curr = curr->next) {
        if (((label_t*)curr->data)->int_pos == asm_data->curr_instr_nbr)
            ((label_t*)curr->data)->byte_pos = asm_data->file_header->prog_size;
        if (((label_t*)curr->data)->int_pos == asm_data->tot_instr_nbr)
            ((label_t*)curr->data)->byte_pos = asm_data->file_header->prog_size
                + instruction->total_bytes;
    }
    asm_data->file_header->prog_size += instruction->total_bytes;
    asm_data->curr_instr_nbr++;
}

/**
 * @brief   Assigns labels to the instruction arguments.
 * @details This function assigns labels to the instruction arguments based on
 *          their positions in the program. It updates the program size in the
 *          header and calculates the corresponding byte positions for the
 *          labeled arguments. If a labeled argument is found, it retrieves the
 *          label from the linked list of labels and calculates the relative
 *          byte position based on the current program size and the total bytes
 *          of the instruction. The calculated value is assigned to the
 *          corresponding argument.
 * @param   header      The program header containing the program size.
 * @param   instruction The instruction to assign labels to.
 * @param   labels      The linked list of labels.
 */
void assign_labels(header_t *header, instruction_t *instruction,
linked_list_t *labels)
{
    int code = instruction->instruction_code -1;
    label_t *tmp = NULL;

    header->prog_size += instruction->total_bytes;
    for (int i = 0; i < op_tab[code].nbr_args; i++) {
        if (instruction->labels_array[i]) {
            tmp = ll_find_label(labels, instruction->labels_array[i])->data;
            instruction->args[i] = tmp->byte_pos - header->prog_size
                + instruction->total_bytes;
        }
    }
}
