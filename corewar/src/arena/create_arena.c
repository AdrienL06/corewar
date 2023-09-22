/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** create_player
*/

#include <stdlib.h>
#include "vm.h"

/**
 * @brief   Fills the arena with program instructions.
 * @details This function fills the arena with program instructions from the
 *          loaded player files. It iterates through each player and their
 *          corresponding program file, starting from their program counter,
 *          and copies the instructions to the arena's battlefield. It checks
 *          for any overlap between instructions and raises an error if an
 *          overlap is detected.
 * @param   data A pointer to the VM data structure.
 */
static void fill_arena(vm_data_t *data)
{
    for (int i = 0, current_pc; i < MAX_PLAYERS; i++) {
        if (!data->arena->players[i] || !data->cor_files[i])
            continue;
        current_pc = data->arena->players[i]->forks->pc;
        for (int j = sizeof(header_t); j < data->cor_files[i]->size; j++) {
            data->arena->battlefield[current_pc + (j - sizeof(header_t))] == 0 ?
                data->arena->battlefield[current_pc + (j - sizeof(header_t))] =
                data->cor_files[i]->bytes[j] :
                exit_vm(data, "[ERROR] Overlap detected!\n", 84);
        }
    }
}

/**
 * @brief   Initializes the program counters for each player.
 * @details This function initializes the program counters for each player in
 *          the arena. It sets the program counter value based on the load
 *          address specified in the command line information. If the load
 *          address is -1, the program counter is set to a calculated value
 *          based on the player's order. The program counters are evenly
 *          distributed across the memory space of the arena.
 * @param   data A pointer to the VM data structure.
 */
static void init_program_counters(vm_data_t *data)
{
    for (int i = 0, j = 0; i < MAX_PLAYERS; i++) {
        if (!data->arena->players[i])
            continue;
        data->arena->players[i]->forks->pc = data->arena->players[i]->forks->pc
        == -1 ? j : data->arena->players[i]->forks->pc;
        j += MEM_SIZE / data->cmd_line_info->nbr_player;
    }
}

/**
 * @brief   Loads the player name from the COR file.
 * @details This function reads the player name from the COR file and assigns it
 *          to the player's name attribute. It opens the file, retrieves the
 *          player name data, and closes the file.
 * @param   data   A pointer to the VM data structure.
 * @param   player A pointer to the player structure.
 * @param   name   The name of the COR file.
 * @param   file   The COR file structure.
 */
static void load_player_name(vm_data_t *data, player_t *player, char *name,
cor_file_t *file)
{

    FILE *fd = fopen(name, "r");

    if (!fd)
        exit_vm_file(data, name, "failed to open");
    my_memset(player->player_name, 0, PROG_NAME_LENGTH + 1);
    for (int i = 0; i < PROG_NAME_LENGTH; i++)
        player->player_name[i] = retrieve_data(
            file->bytes, sizeof(int) + i, sizeof(char));
    fclose(fd);
}

/**
 * @brief   Creates a player in the arena.
 * @details This function creates a player in the arena based on the temporary
 *          player information. It opens the player's file, loads the player's
 *          program into memory, initializes the player's attributes, and
 *          assigns it to the corresponding position in the players array.
 * @param   data     A pointer to the VM data structure.
 * @param   tmp_player The temporary player information.
 * @param   players  The array of player pointers in the arena.
 */
static void create_player(vm_data_t *data, temp_player_t tmp_player,
    player_t **players)
{
    FILE *fd = fopen(tmp_player.filename, "r");
    int prog_nbr;

    if (!fd)
        exit_vm_file(data, tmp_player.filename, "failed to open");
    prog_nbr = cor_file_load(data, tmp_player, fd);
    players[prog_nbr] = malloc(sizeof(player_t));
    load_player_name(data, players[prog_nbr], tmp_player.filename,
        data->cor_files[prog_nbr]);
    players[prog_nbr]->send_live_sig = false;
    players[prog_nbr]->forks = malloc(sizeof(pfork_t));
    players[prog_nbr]->forks->player_name = &*players[prog_nbr]->player_name;
    players[prog_nbr]->forks->next = NULL;
    players[prog_nbr]->forks->carry = false;
    players[prog_nbr]->forks->pc =
        tmp_player.load_address != -1 ? tmp_player.load_address % MEM_SIZE : -1;
    players[prog_nbr]->forks->cooldown = -1;
    my_memset(players[prog_nbr]->forks->registers, 0, 16 * sizeof(reg_t));
    players[prog_nbr]->forks->registers[0] = tmp_player.prog_nbr;
}

/**
 * @brief   Creates the arena for the virtual machine.
 * @details This function initializes the arena structure in the VM data,
 *          allocates memory for the arena, initializes its members, creates
 *          the players in the arena based on the command line information,
 *          initializes program counters, and fills the arena with the player's
 *          instructions.
 * @param   data A pointer to the VM data structure.
 */
void create_arena(vm_data_t *data)
{
    data->arena = malloc(sizeof(arena_t));
    my_memset(data->arena, 0, sizeof(arena_t));
    data->arena->referee = malloc(sizeof(referee_t));
    data->arena->referee->cycle_to_die = CYCLE_TO_DIE;
    data->arena->referee->nb_of_live_call = 0;
    data->arena->referee->last_live_call = 0;
    for (int i = 0; i < MAX_PLAYERS; i++)
        data->arena->referee->players_alive[i] =
                data->arena->players[i] != NULL;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        data->arena->referee->players_alive[i] = false;
        if (!data->cmd_line_info->tmp_players[i].filename)
            continue;
        create_player(data, data->cmd_line_info->tmp_players[i],
                        data->arena->players);
    }
    init_program_counters(data);
    fill_arena(data);
}
