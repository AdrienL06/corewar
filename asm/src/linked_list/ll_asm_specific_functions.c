/*
** EPITECH PROJECT, 2023
** asm
** File description:
** ll_asm_specific_functions
*/

#include "asm.h"

/**
 * @brief   Finds a label in a linked list of labels.
 * @details This function searches for a label with a matching name in the
 *          provided linked list. It iterates through the list and compares
 *          each label's name with the given label string. If a match is found,
 *          it returns the corresponding node in the linked list; otherwise,
 *          it returns NULL.
 * @param   list  The linked list of labels to search.
 * @param   label The label string to search for.
 * @return  Returns the node containing the matching label, or NULL if the label
 *          is not found.
 */
node_t *ll_find_label(linked_list_t *list, char *label)
{
    if (!label)
        return NULL;
    for (node_t *curr = list->head; curr; curr = curr->next)
        if (my_strcmp(((label_t*)curr->data)->name, label) == 0)
            return curr;
    return NULL;
}
