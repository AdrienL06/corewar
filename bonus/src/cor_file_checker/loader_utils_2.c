/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** loader_utils_2
*/

#include "vm.h"

bool can_be_retrieved(int max_size, int start, int size)
{
    if (start + size > max_size)
        return false;
    return true;
}
