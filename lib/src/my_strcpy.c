/*
** EPITECH PROJECT, 2022
** my_strcpy
** File description:
** Function that copies a string into
** another. The destination string
** will already have enough memory
** to copy the source string
*/

#include "lib.h"

/**
* @brief Copies a string from source to destination.
* @param dest The destination string.
* @param src The source string.
* @return A pointer to the destination string.
*/
char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
    return dest;
}

/**
* @brief Copies a string from source to destination with a specified length.
*  If n is greater than the length of src, the remaining characters of dest
*  will be padded with null characters.
* @param dest The destination string.
* @param src The source string.
* @param n The maximum number of characters to be copied.
* @return A pointer to the destination string.
*/
char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;
    int len = my_strlen(src);

    while (i < n) {
        dest[i] = src[i];
        i++;
    }
    if (n > len) {
        i++;
    }
    dest[i] = src[len];
    return dest;
}
