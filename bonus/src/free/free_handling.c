/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** All functions related to freeing memory
*/

#include <stdlib.h>
#include "vm.h"

int display_file_error(char *filename, const char *str1, const char *str2,
int return_value)
{
    ERROR_WRITE("[ERROR] File \"", 14);
    ERROR_WRITE(filename, my_strlen(filename));
    ERROR_WRITE("\" ", 2);
    ERROR_WRITE(str1, my_strlen(str1));
    ERROR_WRITE(str2, my_strlen(str2));
    return return_value;
}

void exit_vm_file(vm_data_t *data, char *filename, char *error_msg)
{
    display_file_error(filename, error_msg, "", 0);
    exit_vm(data, "\n", FAILURE);
}

void free_pforks(pfork_t *pfork)
{
    pfork_t *to_free = NULL;

    for (pfork_t *curr = pfork; curr;) {
        to_free = curr;
        curr = curr->next;
        free(to_free);
    }
}

void free_arena(vm_data_t *data)
{
    if (data->arena == NULL)
        return;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!data->arena->players[i])
            continue;
        free_pforks(data->arena->players[i]->forks);
        free(data->arena->players[i]);
    }
    free(data->arena->referee);
    free(data->arena);
}

void exit_vm(vm_data_t *data, const char *message, int exit_code)
{
    if (exit_code == FAILURE) {
        ERROR_WRITE(message, my_strlen(message));
    }
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!data->cor_files[i])
            continue;
        free(data->cor_files[i]->bytes);
        free(data->cor_files[i]);
    }
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!data->cmd_line_info->tmp_players[i].filename)
            continue;
        free(data->cmd_line_info->tmp_players[i].filename);
    }
    free(data->cmd_line_info);
    free_arena(data);
    free(data);
    exit(exit_code);
}
