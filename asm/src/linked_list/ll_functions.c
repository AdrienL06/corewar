/*
** EPITECH PROJECT, 2023
** linked lists
** File description:
** functions
*/

#include <stdlib.h>
#include "linked_list.h"
#include "../../lib/include/lib.h"

/**
 * @brief   Initializes a new linked list in the Corewar program.
 * @details This function allocates memory for a new linked list structure,
 *          initializes its members, and optionally assigns destructor
 *          functions to the list's destructor array.
 * @param   destructors An array of destructor functions to be assigned to the
 *          linked list's destructor array. Pass NULL if no destructor
 *          functions need to be assigned.
 * @return  A pointer to the newly created linked list structure.
 */
linked_list_t *ll_init(destructor_t destructors[MAX_DESTRUCTOR_NBR])
{
    linked_list_t *list = malloc(sizeof(linked_list_t));

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    if (destructors)
        for (int i = 0; i < MAX_DESTRUCTOR_NBR; i++)
            list->destructors[i] = destructors[i];
    return list;
}

/**
 * @brief   Frees the memory used by a linked list in the Corewar program.
 * @details This function frees the memory allocated for the linked list
 *          structure and its nodes, invoking the appropriate destructor
 *          functions if provided.
 * @param   list A pointer to the linked list structure to be freed.
 */
void ll_free(linked_list_t *list)
{
    node_t *to_free = NULL;

    for (node_t *curr = list->head; curr;) {
        if (list->destructors[curr->type])
            list->destructors[curr->type](curr->data);
        to_free = curr;
        curr = curr->next;
        free(to_free);
    }
    free(list);
}

/**
 * @brief   Adds a new node with the specified data at the end of a linked
 *          list in the Corewar program.
 * @details This function creates a new node, assigns the specified data and
 *          node type to it, and adds the node at the end of the linked list.
 *          If the list is empty, the new node becomes the head and the tail
 *          of the list.
 * @param   list A pointer to the linked list structure.
 * @param   data A pointer to the data to be stored in the new node.
 * @param   type The type of the new node.
 */
void ll_add_to_end(linked_list_t *list, void *data, node_type_t type)
{
    node_t *new = malloc(sizeof(node_t));
    new->type = type;
    new->data = data;
    new->next = NULL;
    list->size++;
    if (list->size == 1) {
        list->head = new;
        list->tail = new;
        return;
    }
    list->tail->next = new;
    list->tail = new;
}
