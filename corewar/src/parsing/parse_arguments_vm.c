/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** Parse the command line arguments
*/

#include <unistd.h>
#include "vm.h"

/**
 * @brief   Displays the help information.
 * @details This function writes the usage information, dump usage, program
 *          number usage, and load address usage to the standard output. It then
 *          exits the program with a success status code.
 * @param   data A pointer to the VM data structure.
 */
static void display_help(vm_data_t *data)
{
    write(1, USAGE);
    write(1, DUMP_USAGE);
    write(1, PROG_NUMBER_USAGE);
    write(1, LOAD_ADDR_USAGE);
    exit_vm(data, NULL, SUCCESS);
}

/**
 * @brief   Gets the first available program number.
 * @details This function returns the first available program number for a
 *          player. If the player already has a program number assigned, that
 *          number is returned. Otherwise, it searches for the first available
 *          program number in the command line information and marks it as
 *          unavailable.
 * @param   info   A pointer to the command line information.
 * @param   player The temporary player structure.
 * @return  The program number.
 */
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

/**
 * @brief   Sets the program numbers for each player.
 * @details This function sets the program numbers for each player based on the
 *          available program numbers. It ensures that no two players have the
 *          same program number.
 * @param   data A pointer to the VM data structure.
 */
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

/**
 * @brief   Parses the command line arguments.
 * @details This function parses the command line arguments passed to the
 *          program. It checks the number of arguments, handles the help option,
 *          fills the VM data structure with the command line information, sets
 *          the program numbers, and validates the number of players.
 * @param   ac   The number of command line arguments.
 * @param   av   The array of command line arguments.
 * @param   data A pointer to the VM data structure.
 */
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
