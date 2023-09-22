/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** fork
*/

#include <stdlib.h>
#include "vm.h"

/**
 * @brief   Creates a new process (fork) in the list of processes.
 * @details This function creates a new process (fork) by dynamically allocating
 *          memory for a new `pfork_t` structure and adding it to the end of the
 *          list of processes. The new process inherits the program counter
 *          (PC), carry flag, cooldown, and registers of the parent process.
 * @param   player  The parent process from which to create the fork.
 * @param   new_pc  The program counter (PC) of the new process.
 */
void create_new_fork(pfork_t *player, int new_pc)
{
    pfork_t *end_of_list = NULL;

    for (end_of_list = player; end_of_list->next;
    end_of_list = end_of_list->next);
    end_of_list->next = malloc(sizeof(pfork_t));
    end_of_list->next->next = NULL;
    end_of_list->next->pc = new_pc;
    end_of_list->next->carry = player->carry;
    end_of_list->next->cooldown = -1;
    for (int i = 0; i < 16; i++)
        end_of_list->next->registers[i] = player->registers[i];
    end_of_list->next->player_name = player->player_name;
}

/**
 * @brief   Executes the FORK instruction.
 * @details This function executes the FORK instruction, which creates a new
 *          process at a specified offset from the current program counter (PC)
 *          of the executing process. The offset is calculated based on the
 *          value of the first argument. The new process is added to the list
 *          of processes in the arena.
 * @param   arena   The arena containing the battlefield.
 * @param   player  The process executing the instruction.
 * @param   args    The arguments of the instruction.
 * @return  The size of the instruction in bytes.
 */
int fork_run(arena_t *arena, pfork_t *player, instruction_arg_t *args)
{
    int arg1 = get_argument_value(&args[0], player, arena);
    int new_pc = player->pc + (arg1 % IDX_MOD);

    create_new_fork(player, new_pc);
    return get_instruction_size(args, op_tab[I_FORK]);
}
