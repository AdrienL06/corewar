/*
** EPITECH PROJECT, 2023
** asm
** File description:
** args_handling
*/

#include <unistd.h>
#include <stdlib.h>
#include "asm.h"

/**
 * @brief   Checks the type of command-line arguments in the Corewar program.
 * @details This function verifies the number and format of command-line
 *          arguments. If the number of arguments is invalid or if the argument
 *          is "-h", it displays the appropriate usage information and exits
 *          the program.
 * @param   asm_data A pointer to the `asm_data_t` structure containing the
 *          program data.
 * @param   ac The number of command-line arguments.
 * @param   av An array of strings containing the command-line arguments.
 */
void check_arguments_type(asm_data_t *asm_data, int ac, char **av)
{
    if (ac != 2)
        exit_asm(asm_data, "Invalid number of arguments!\n", FAILURE);
    if (my_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'h') {
        write(1, "USAGE\n\t./asm file_name[.s]\nDESCRIPTION\n\tfile_name file "
        "in assembly language to be converted into file_name.cor, an "
        "executable in the Virtual Machine.\n", 150);
        exit_asm(asm_data, NULL, SUCCESS);
    }
}
