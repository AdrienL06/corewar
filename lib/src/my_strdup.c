/*
** EPITECH PROJECT, 2023
** librairie
** File description:
** my_strdup
*/

#include "lib.h"
#include <stdlib.h>

/**
* @brief Allocates a new string, copies the contents of a given string
*  to it, and returns a pointer to the new string.
* @param str The string to duplicate.
* @return A pointer to the new string.
*/
char *my_strdup(char *str)
{
    char *result = malloc(sizeof(char) * (my_strlen(str) + 1));
    int index = 0;

    for (; str[index]; index++)
        result[index] = str[index];
    result[index] = '\0';
    return result;
}
