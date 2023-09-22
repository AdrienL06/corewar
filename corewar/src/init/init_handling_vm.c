/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** All functions related to initializing the program
*/

#include <stdlib.h>
#include "vm.h"

/**
 * @brief   Initializes the instruction function pointers.
 * @details This function assigns the appropriate function pointers to the
 *          instruction execution functions in the op_tab array.
 *          Each instruction's execution function is assigned to its respective
 *          op_tab entry.
 */
void init_instruction_fn(void)
{
    op_tab[I_LIVE].exec = &live_run;
    op_tab[I_LD].exec = &ld_run;
    op_tab[I_ST].exec = &st_run;
    op_tab[I_ADD].exec = &add_run;
    op_tab[I_SUB].exec = &sub_run;
    op_tab[I_AND].exec = &and_run;
    op_tab[I_OR].exec = &or_run;
    op_tab[I_XOR].exec = &xor_run;
    op_tab[I_ZJMP].exec = &zjmp_run;
    op_tab[I_LDI].exec = &ldi_run;
    op_tab[I_STI].exec = &sti_run;
    op_tab[I_FORK].exec = &fork_run;
    op_tab[I_LLD].exec = &lld_run;
    op_tab[I_LLDI].exec = &lldi_run;
    op_tab[I_LFORK].exec = &lfork_run;
    op_tab[I_AFF].exec = &aff_run;
}

/**
 * @brief   Initializes a temporary player in the VM data structure.
 * @details This function sets the filename, program number, and load address
 *          for a temporary player in the VM data structure.
 * @param   data      A pointer to the VM data structure.
 * @param   filename  The filename of the player.
 * @param   args      Structure containing the program number (n) and load
 *                    address (a) for the player.
 */
void init_temp_player(vm_data_t *data,
                    char *filename, fn_args_init_player_t args)
{
    if (filename[0] == '-')
        exit_vm(data, "[ERROR] Unrecognized option\n", FAILURE);
    if (args.nbr_player > MAX_PLAYERS - 1)
        exit_vm(data, "[ERROR] Too many players\n", FAILURE);
    data->cmd_line_info->tmp_players[args.nbr_player].filename = my_strdup(
                                                                    filename);
    data->cmd_line_info->tmp_players[args.nbr_player].prog_nbr = args.n;
    data->cmd_line_info->tmp_players[args.nbr_player].load_address = args.a;
}

/**
 * @brief   Initializes the VM data structure.
 * @details This function allocates memory for the VM data structure,
 *          initializes its members, and sets default values for command line
 *          information and players.
 * @return  A pointer to the initialized VM data structure.
 */
vm_data_t *init_vm_data(void)
{
    vm_data_t *data = malloc(sizeof(vm_data_t));

    my_memset(data, 0, sizeof(vm_data_t));
    data->cmd_line_info = malloc(sizeof(command_line_info_t));
    my_memset(data->cmd_line_info, 0, sizeof(command_line_info_t));
    data->cmd_line_info->dump_nbr_cycle = -1;
    for (int i = 0; i < 4; i++) {
        data->cmd_line_info->tmp_players[i].prog_nbr = PARSING_DEFAULT_VALUE;
        data->cmd_line_info->tmp_players[i].filename = NULL;
        data->cmd_line_info->tmp_players[i].load_address =
                PARSING_DEFAULT_VALUE;
        data->cmd_line_info->availaible_prog_nbr[i] = true;
    }
    data->arena = NULL;
    init_instruction_fn();
    return data;
}
