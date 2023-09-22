/*
** EPITECH PROJECT, 2023
** delivery
** File description:
** my_str
*/

#include "lib.h"
#include <stdlib.h>

/**
* @brief Locates the first occurrence of a substring within a string.
* @param str The string to search in.
* @param to_find The substring to search for.
* @return A pointer to the first occurrence of the substring to_find in str,
*  or NULL if it is not found.
*/
char *my_strstr(char *str, char const *to_find)
{
    if (str == NULL || to_find == NULL)
        return NULL;
    if (to_find[0] == '\0')
        return str;
    for (size_t i = 0; str[i] != '\0'; i++) {
        size_t j = 0;
        while (str[i + j] == to_find[j] && to_find[j] != '\0')
            j++;
        if (to_find[j] == '\0')
            return str + i;
    }
    return NULL;
}
