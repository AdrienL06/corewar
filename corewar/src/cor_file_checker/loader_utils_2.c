/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** loader_utils_2
*/

#include "vm.h"

/**
 * @brief  Checks if data can be retrieved from a given range within a buffer.
 * @param  max_size The maximum size of the buffer.
 * @param  start    The starting position to retrieve data from.
 * @param  size     The size of the data to retrieve.
 * @return Returns true if the data can be retrieved, false otherwise.
 */
bool can_be_retrieved(int max_size, int start, int size)
{
    if (start + size > max_size)
        return false;
    return true;
}
