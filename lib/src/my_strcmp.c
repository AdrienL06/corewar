/*
** EPITECH PROJECT, 2022
** my_strcmp
** File description:
** Function that compare two character strings
*/

/**
 * @brief Compares two strings. This function compares the two null-terminated
 *  strings `s1` and `s2`.
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return An integer less than, equal to, or greater than zero if `s1` is
 *  found, respectively, to be less than, to match, or be greater than `s2`.
 */
int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            break;
        i++;
    }
    return s1[i] - s2[i];
}

/**
* @brief Compares the first n characters of two strings.
* @param s1 The first string to compare.
* @param s2 The second string to compare.
* @param n The maximum number of characters to compare.
* @return An integer less than, equal to, or greater than zero if s1 is found,
*  respectively, to be less than, to match, or be greater than s2.
*/
int my_strncmp(const char *s1, const char *s2, int n)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && i < n - 1) {
        if (s1[i] != s2[i])
            break;
        i++;
    }
    return s1[i] - s2[i];
}
