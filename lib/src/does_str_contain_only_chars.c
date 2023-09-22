/*
** EPITECH PROJECT, 2023
** does_str_contain_only_chars
** File description:
** does_str_contain_only_chars
*/

#include <stdbool.h>
#include "lib.h"

/**
* @brief Checks if a string contains only a given set of characters
* @param str The string to check
* @param chars A null-terminated string representing the set of
*  characters allowed
* @return true if the string contains only characters from the
*  given set, false otherwise
*/
bool does_str_contain_only_chars(char *str, const char *chars)
{
    for (int i = 0; str[i]; i++)
        if (!is_char_in_str(str[i], chars))
            return false;
    return true;
}
