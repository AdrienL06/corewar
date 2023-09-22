/*
** EPITECH PROJECT, 2023
** my_atoi
** File description:
** my_atoi
*/

#include "lib.h"

/**
* @brief Converts a string to an integer.
* @param str The string to convert.
* @param endptr A pointer to a character that will be set to the first
*  character not converted if the entire string is not converted.
* @return The integer value of the string, or 0 if the string is not a
*  valid integer.
*/
int my_atoi(const char *str, char *endptr)
{
    int result = 0;
    int i = 0;
    int negative_coeff = (str && *str == '-') ? -1 : 1;

    if (!str) {
        *endptr = '-';
        return 0;
    }
    if (my_strncmp(str, "-2147483648", 12) == 0) {
        *endptr = str[my_strlen(str)];
        return -2147483648;
    }
    *str == '-' ? str++ : 0;
    for (; str[i] != '\0' && str[i] != '\n'; i++) {
        if (str[i] < '0' || str[i] > '9')
            break;
        result = result * 10 + (str[i] - '0');
    }
    *endptr = (char)((*str == '\0') ? '-' : str[i]);
    return result * negative_coeff;
}
