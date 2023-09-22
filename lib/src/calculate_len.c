/*
** EPITECH PROJECT, 2022
** my_strlen
** File description:
** Function that counts and returns the
** number of characters found in
** the string passed as parameter.
*/

/**
* @brief Computes the length of a given string.
* @param str The string to compute the length of.
* @return The length of the string.
*/
int my_strlen(char *str)
{
    int result = 0;

    for (int i = 0; str[i]; i++)
        result++;
    return result;
}

/**
* @brief Computes the length of a null-terminated array of strings.
* @param arr The array of strings to compute the length of.
* @return The number of strings in the array, excluding the null-terminating
*  string.
*/
int my_arrlen(char **arr)
{
    int result = 0;

    for (int i = 0; arr[i]; i++)
        result++;
    return result;
}
