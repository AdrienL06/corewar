/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** create_player
*/

#include <stdlib.h>
#include "vm.h"


static void fill_arena(vm_data_t *data)
{
    for (int i = 0; i < MEM_SIZE; i++) {
        data->arena->nattr[i] = C_DEFAULT;
    }
    for (int i = 0, current_pc; i < MAX_PLAYERS; i++) {
        if (!data->arena->players[i] || !data->cor_files[i])
            continue;
        current_pc = data->arena->players[i]->forks->pc;
        for (int j = sizeof(header_t); j < data->cor_files[i]->size; j++) {
            data->arena->battlefield[current_pc + (j - sizeof(header_t))] == 0 ?
                data->arena->battlefield[current_pc + (j - sizeof(header_t))] =
                data->cor_files[i]->bytes[j] :
                exit_vm(data, "[ERROR] Overlap detected!\n", 84);
            data->arena->nattr[current_pc + (j - sizeof(header_t))] = C_DEFAULT + i + 1;
        }
    }
    //FILE *debug = fopen("debug.txt", "w");
    //for (int i = 0; i < MEM_SIZE; i++) {
    //    fprintf(debug, "%d", data->arena->nattr[i]);
    //}
    //fclose(debug);
}

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
    players[prog_nbr]->color = C_DEFAULT + prog_nbr + 1;
    players[prog_nbr]->forks = malloc(sizeof(pfork_t));
    players[prog_nbr]->forks->player_name = &*players[prog_nbr]->player_name;
    players[prog_nbr]->forks->next = NULL;
    players[prog_nbr]->forks->carry = false;
    players[prog_nbr]->forks->pc =
        tmp_player.load_address != -1 ? tmp_player.load_address % MEM_SIZE : -1;
    players[prog_nbr]->forks->cooldown = -1;
    my_memset(players[prog_nbr]->forks->registers, 0, 16 * sizeof(reg_t));
    players[prog_nbr]->forks->registers[0] = tmp_player.prog_nbr;
    players[prog_nbr]->forks->color = &players[prog_nbr]->color;
}

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
