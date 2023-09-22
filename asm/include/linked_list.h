/*
** EPITECH PROJECT, 2023
** asm
** File description:
** linked_list
*/

#ifndef LINKED_LIST_H_
    #define LINKED_LIST_H_

// ========================== [DEFINES & TYPEDEFS] ========================== //

    #define MAX_DESTRUCTOR_NBR MAX_NODE_TYPE_NBR
    typedef void (*destructor_t)(void*);

// ================================ [ENUMS] ================================= //

    typedef enum node_type {
        T_NONE,
        T_LABEL,
        T_INSTRUCTION,
        MAX_NODE_TYPE_NBR,
    } node_type_t;

// ============================== [STRUCTURES] ============================== //

    typedef struct node_s {
        int type;
        void *data;
        struct node_s *next;
    } node_t;

    typedef struct linked_list_s {
        int size;
        node_t *head;
        node_t *tail;
        destructor_t destructors[MAX_DESTRUCTOR_NBR];
    } linked_list_t;

// ============================= [DECLARATIONS] ============================= //

    linked_list_t *ll_init(destructor_t destructors[MAX_DESTRUCTOR_NBR]);
    void ll_free(linked_list_t *list);
    void ll_add_to_end(linked_list_t *list, void *data, node_type_t type);
    node_t *ll_find_label(linked_list_t *list, char *label);

// ========================================================================== //
#endif /* !LINKED_LIST_H_ */
