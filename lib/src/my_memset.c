/*
** EPITECH PROJECT, 2023
** my_memset
** File description:
** my_memset
*/

#include <sys/types.h>

/**
 * @brief Fills the first n bytes of the memory area pointed to by s with the
 * constant byte c.
 * @param s Pointer to the memory area to be filled.
 * @param c Constant.
 * @param n Number of bytes to fill.
 * @return A pointer to the memory area s.
*/
void *my_memset(void *s, int c, size_t n)
{
    unsigned char *tmp = s;

    for (size_t i = 0; i < n; i++)
        tmp[i] = c;
    return s;
}
