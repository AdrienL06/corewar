/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** All functions related to freeing memory
*/

#include <stdlib.h>
#include "vm.h"

/**
 * @brief  Displays an error message related to a file operation.
 * @param  filename        The name of the file.
 * @param  str1            The first part of the error message.
 * @param  str2            The second part of the error message.
 * @param  return_value    The return value to be returned by the function.
 * @return The specified return value.
 */
int display_file_error(char *filename, const char *str1, const char *str2,
int return_value)
{
    ERROR_WRITE_VM("[ERROR] File \"", 14);
    ERROR_WRITE_VM(filename, my_strlen(filename));
    ERROR_WRITE_VM("\" ", 2);
    ERROR_WRITE_VM(str1, my_strlen(str1));
    ERROR_WRITE_VM(str2, my_strlen(str2));
    return return_value;
}

/**
 * @brief Handles file-related errors during the execution of the virtual
 *        machine. Displays an error message and exits the program.
 * @param data        The vm_data_t structure.
 * @param filename    The name of the file that caused the error.
 * @param error_msg   The error message describing the failure.
 */
void exit_vm_file(vm_data_t *data, char *filename, char *error_msg)
{
    display_file_error(filename, error_msg, "", 0);
    exit_vm(data, "\n", FAILURE);
}

/**
 * @brief Frees the memory allocated for a linked list of pfork_t structures.
 * @param pfork   The head of the linked list.
 */
void free_pforks(pfork_t *pfork)
{
    pfork_t *to_free = NULL;

    for (pfork_t *curr = pfork; curr;) {
        to_free = curr;
        curr = curr->next;
        free(to_free);
    }
}

/**
 * @brief Frees the memory allocated for the arena and its associated
 *        structures.
 * @param data    The VM data structure.
 */
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

/**
 * @brief   Exits the virtual machine and cleans up allocated resources.
 * @details This function is called to gracefully exit the virtual machine.
 *          It prints an error message if the exit code is set to FAILURE,
 *          frees allocated memory, and terminates the program.
 * @param   data        The VM data structure.
 * @param   message     The error message (if applicable).
 * @param   exit_code   The exit code for the program.
 */
void exit_vm(vm_data_t *data, const char *message, int exit_code)
{
    if (exit_code == FAILURE) {
        ERROR_WRITE_VM(message, my_strlen(message));
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
