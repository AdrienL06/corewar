/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** Set arguments' info
*/

#include <unistd.h>
#include "vm.h"

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
