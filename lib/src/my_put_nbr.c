/*
** EPITECH PROJECT, 2022
** my_put_nbr
** File description:
** Displays the number given as a parameter.
*/

#include <unistd.h>

/**
 * @brief Prints an integer to the standard output.
 *  This function prints the given integer to the standard output. If the
 *  integer is negative, a '-' sign is printed before the number. The function
 *  returns 0 on success.
 * @param nb The integer to print.
 * @return 0.
 */
int my_put_nbr(int nb)
{
    char c;

    if (nb == -2147483648)
        return (int)write(1, "-2147483648", 11);
    if (nb < 0) {
        nb *= -1;
        write(1, "-", 1);
    }
    if (nb >= 10)
        my_put_nbr(nb / 10);
    c = (char)('0' + nb % 10);
    write(1, &c, 1);
    return 0;
}
