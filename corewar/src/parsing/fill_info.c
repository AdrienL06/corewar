/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** Set arguments' info
*/

#include <unistd.h>
#include "vm.h"

/**
 * @brief   Sets the program number for a player in the VM data structure.
 * @details This function extracts the program number from the command line
 *          arguments and sets it for a specific player in the VM data
 *          structure. It performs validation to ensure that the program number
 *          is a valid integer between 1 and 4 and that the option is properly
 *          formatted.
 * @param   data A pointer to the VM data structure.
 * @param   argv The array of command line arguments.
 * @param   i    A pointer to the current index in the command line arguments.
 * @param   n    A pointer to the variable storing the program number.
 */
static void set_n(vm_data_t *data, char **argv, int *i, int *n)
{
    char endptr = '\0';

    if (!argv[*i + 1] || !argv[*i + 2])
        exit_vm(data, "[ERROR] -n option | No player\n", FAILURE);
    *n = (*n == PARSING_DEFAULT_VALUE) ? my_atoi(argv[*i + 1], &endptr)
                                        : PARSING_ERROR_VALUE;
    if (endptr != '\0')
        exit_vm(data, "[ERROR] -n option | Invalid number\n", FAILURE);
    if (*n == PARSING_ERROR_VALUE)
        exit_vm(data, "[ERROR] -n option | Number already set\n", FAILURE);
    if (*n < 1 || *n > 4)
        exit_vm(data, "[ERROR] -n option | Number must be between 1 and 4\n",
                FAILURE);
    data->cmd_line_info->availaible_prog_nbr[*n - 1] = false;
    (*i)++;
}

/**
 * @brief   Sets the load address for a player in the VM data structure.
 * @details This function extracts the load address from the command line
 *          arguments and sets it for a specific player in the VM data
 *          structure. It performs validation to ensure that the load address is
 *          a valid positive integer and that the option is properly formatted.
 * @param   data A pointer to the VM data structure.
 * @param   argv The array of command line arguments.
 * @param   i    A pointer to the current index in the command line arguments.
 * @param   a    A pointer to the variable storing the load address.
 */
static void set_a(vm_data_t *data, char **argv, int *i, int *a)
{
    char endptr = '\0';

    if (!argv[*i + 1] || !argv[*i + 2])
        exit_vm(data, "[ERROR] -a option | No player\n", FAILURE);
    *a = (*a == PARSING_DEFAULT_VALUE) ? my_atoi(argv[*i + 1], &endptr)
                                        : PARSING_ERROR_VALUE;
    if (endptr != '\0')
        exit_vm(data, "[ERROR] -a option | Invalid number\n", FAILURE);
    if (*a == PARSING_ERROR_VALUE)
        exit_vm(data, "[ERROR] -a option | Number already set\n", FAILURE);
    if (*a < 0)
        exit_vm(data, "[ERROR] -a option | Number must be positive\n", FAILURE);
    (*i)++;
}

/**
 * @brief   Sets the dump number of cycles in the VM data structure.
 * @details This function extracts the dump number of cycles from the command
 *          line arguments and stores it in the VM data structure. It performs
 *          validation to ensure that the dump number is a valid positive
 *          integer.
 * @param   data A pointer to the VM data structure.
 * @param   argv The array of command line arguments.
 * @param   i    A pointer to the current index in the command line arguments.
 */
static void set_dump(vm_data_t *data, char **argv, int *i)
{
    char endptr = '\0';

    data->cmd_line_info->dump_nbr_cycle = my_atoi(argv[*i + 1], &endptr);
    if (endptr != '\0')
        exit_vm(data, "[ERROR] -dump option | Invalid number\n", FAILURE);
    if (data->cmd_line_info->dump_nbr_cycle < 0)
        exit_vm(data, "[ERROR] -dump option | Number must be positive\n",
            FAILURE);
    (*i) += 2;
}

/**
 * @brief   Fills the command line information in the VM data structure.
 * @details This function parses the command line arguments starting from index
 *          1. It checks for the "-dump" option, sets the program numbers ("-n"
 *          option), sets the load addresses ("-a" option), and initializes
 *          temporary players based on the remaining arguments. The number of
 *          players is incremented for each initialized player.
 * @param   argc The number of command line arguments.
 * @param   argv The array of command line arguments.
 * @param   data A pointer to the VM data structure.
 */
void fill_info(int argc, char **argv, vm_data_t *data)
{
    int i = 1;

    if (!my_strcmp(argv[i], "-dump"))
        set_dump(data, argv, &i);
    for (int n = PARSING_DEFAULT_VALUE, a = PARSING_DEFAULT_VALUE;
        i < argc; i++) {
        if (!my_strcmp(argv[i], "-n")) {
            set_n(data, argv, &i, &n);
            continue;
        }
        if (!my_strcmp(argv[i], "-a")) {
            set_a(data, argv, &i, &a);
            continue;
        }
        init_temp_player(data, argv[i],
                (fn_args_init_player_t){data->cmd_line_info->nbr_player, n, a});
        data->cmd_line_info->nbr_player++;
        n = PARSING_DEFAULT_VALUE;
        a = PARSING_DEFAULT_VALUE;
    }
}
