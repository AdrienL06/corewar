/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** Parse the command line arguments
*/

#include <unistd.h>
#include "vm.h"

static void display_help(vm_data_t *data)
{
    write(1, USAGE);
    write(1, DUMP_USAGE);
    write(1, PROG_NUMBER_USAGE);
    write(1, LOAD_ADDR_USAGE);
    exit_vm(data, NULL, SUCCESS);
}

static int get_free_first_prog_number(command_line_info_t *info,
        temp_player_t player)
{
    int i = 0;

    if (player.prog_nbr != PARSING_DEFAULT_VALUE)
        return player.prog_nbr;
    for (; i < 4; i++) {
        if (info->availaible_prog_nbr[i] == true) {
            info->availaible_prog_nbr[i] = false;
            return i + 1;
        }
    }
    return i;
}

static void set_prog_nbr(vm_data_t *data)
{
    command_line_info_t *info = data->cmd_line_info;

    for (int i = 0; i < info->nbr_player; i++) {
        info->tmp_players[i].prog_nbr = get_free_first_prog_number(info,
            info->tmp_players[i]);
        for (int j = 0; j < info->nbr_player; j++) {
            (i != j &&
                info->tmp_players[i].prog_nbr == info->tmp_players[j].prog_nbr)
                ? exit_vm(data,"[ERROR] Two players can't have the same "
                                "prog_nbr\n", FAILURE) : 0;
        }
    }
}

void parse_arguments(int ac, char **av, vm_data_t *data)
{
    if (ac < 2)
        exit_vm(data, "[ERROR] Not enough arguments\n", FAILURE);
    if (ac == 2 && my_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'h')
        display_help(data);
    fill_info(ac, av, data);
    set_prog_nbr(data);
    if (data->cmd_line_info->nbr_player <= 1)
        exit_vm(data, "[ERROR] Not enough players\n", FAILURE);
}
