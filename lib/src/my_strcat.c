/*
** EPITECH PROJECT, 2022
** my_strcat
** File description:
** Function that concatenates two strings
*/

#include <stdlib.h>
#include "lib.h"

/**
* @brief Concatenates two strings.
* @param dest The destination string.
* @param src The source string.
* @return A pointer to the destination string.
*/
char *my_strcat(char *dest, char const *src)
{
    int s1 = my_strlen(dest);
    int s2 = 0;

    while (src[s2] != '\0') {
        dest[s1 + s2 - 1] = src[s2];
        s2++;
    }
    dest[s1 + s2 - 1] = '\0';
    return dest;
}

/**
* @brief The function appends the first nb characters of the string src to
*  the end of the string dest.
* @param dest The destination string.
* @param src The source string.
* @param nb The maximum number of characters to be appended.
* @return A pointer to the destination string.
*/
char *my_strncat(char *dest, char *src, int nb)
{
    int i = my_strlen(dest);
    int j = 0;

    while (j < nb && src[j] != '\0') {
        dest[i + j] = src[j];
        j++;
    }
    dest[i + j] = '\0';
    return dest;
}

/**
* @brief Concatenates two strings dynamically. The memory for the concatenated
*  string is allocated dynamically and must be freed by the caller.
* @param left The left-hand side string.
* @param right The right-hand side string.
* @return A pointer to the concatenated string.
*/
char *my_mstrcat(char *left, const char *right)
{
    int left_len = my_strlen(left);
    int right_len = my_strlen(right);
    char *result = malloc(sizeof(char) * (left_len + right_len + 1));

    result[left_len + right_len] = '\0';
    for (int i = 0; i < left_len; i++)
        result[i] = left[i];
    for (int i = 0; i < right_len; i++)
        result[left_len + i] = right[i];
    return result;
}

/**
* @brief Concatenates three strings with a delimiter between left and
*  right strings.
* @param left The left string.
* @param delim The delimiter string.
* @param right The right string.
* @return A newly allocated string which is the concatenation of the three
*  input strings with the delimiter. It should be freed by the caller when no
*  longer needed.
*/
char *my_strcat_delim(char *left, char *delim, char *right)
{
    char *result = NULL;
    int left_len = my_strlen(left);
    int delim_len = my_strlen(delim);
    int right_len = my_strlen(right);
    int index = 0;

    result = malloc(sizeof(char) * (left_len + delim_len + right_len + 1));
    for (; index < left_len; index++, left++)
        result[index] = *left;
    for (; index < left_len + delim_len; index++, delim++)
        result[index] = *delim;
    for (; index < left_len + delim_len + right_len; index++, right++)
        result[index] = *right;
    result[left_len + delim_len + right_len] = '\0';
    return result;
}
