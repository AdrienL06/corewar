/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Scheduler
*/

#include <unistd.h>
#include "vm.h"

/**
 * @brief   Writes an 8-bit unsigned integer in hexadecimal format.
 * @details This function writes an 8-bit unsigned integer in hexadecimal
 *          format to the standard output. It uses a lookup table `hex` to
 *          map each nibble of the integer to its corresponding hexadecimal
 *          character and writes the two hexadecimal characters separately.
 * @param   nbr The 8-bit unsigned integer to write in hexadecimal format.
 */
static void write_int8t_in_hex(u_int8_t nbr)
{
    const char *hex = "0123456789ABCDEF";

    write(1, &hex[nbr / 16], 1);
    write(1, &hex[nbr % 16], 1);
}

/**
 * @brief   Writes a 16-bit unsigned integer in hexadecimal format.
 * @details This function writes a 16-bit unsigned integer in hexadecimal
 *          format to the standard output. It first divides the number by 256
 *          to obtain the most significant byte, and then writes the two
 *          bytes (most significant and least significant) separately using
 *          the `write_int8t_in_hex` function.
 * @param   nbr The 16-bit unsigned integer to write in hexadecimal format.
 */
static void write_int16t_in_hex(u_int16_t nbr)
{
    write_int8t_in_hex(nbr / 256);
    write_int8t_in_hex(nbr % 256);
}

/**
 * @brief   Dumps the memory contents to the standard output.
 * @details This function dumps the memory contents to the standard output.
 *          It iterates through the memory and prints the hexadecimal
 *          representation of each byte. The memory is displayed in rows of
 *          32 bytes, with the corresponding memory address at the beginning
 *          of each row.
 * @param   data A pointer to the VM data structure.
 */
static void dump_mem(vm_data_t *data)
{
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i % 32 == 0) {
            i != 0 ? write(1, "\n", 1) : 0;
            write_int16t_in_hex(i);
            write(1, ": ", 2);
        }
        write_int8t_in_hex(data->arena->battlefield[i]);
        if (i + 1 != MEM_SIZE)
            (i + 1) % 32 != 0 ? write(1, " ", 1) : 0;
    }
    write(1, "\n", 1);
}

/**
 * @brief   Executes instructions for each program fork of a player.
 * @details This function executes instructions for each program fork of a
 *          player. It iterates through each program fork and performs the
 *          necessary operations based on the cooldown of the fork. If the
 *          cooldown is 0, the instruction is executed. The cooldown is then
 *          updated based on the number of cycles required for the instruction.
 *          Additionally, if the number of live calls exceeds the threshold,
 *          the cycle_to_die is decreased.
 * @param   player A pointer to the player.
 * @param   arena  A pointer to the arena.
 */
static void exec_instruction_pforks(player_t *player, arena_t *arena)
{
    for (pfork_t *curr = player->forks; curr; curr = curr->next) {
        curr->cooldown = curr->cooldown == -1 ?
                find_instruction(
                        arena->battlefield[curr->pc % MEM_SIZE]).nbr_cycles :
                curr->cooldown;
        if (curr->cooldown == 0) {
            exec_instruction(curr, arena);
            curr->cooldown = find_instruction(
                    arena->battlefield[curr->pc % MEM_SIZE]).nbr_cycles;
        }
        curr->cooldown--;
        if (arena->referee->nb_of_live_call >= NBR_LIVE) {
            arena->referee->cycle_to_die -= CYCLE_DELTA;
            arena->referee->nb_of_live_call = 0;
        }
    }
}

/**
 * @brief   Starts the virtual machine.
 * @details This function starts the virtual machine by executing instructions
 *          in a loop until the termination conditions are met. It iterates
 *          through each player and executes the instruction for each program
 *          fork. It checks the cycle count to determine when to perform
 *          referee checks and when to trigger memory dumps. The function
 *          updates the current cycle count and continues until the termination
 *          conditions are met.
 * @param   data A pointer to the VM data structure.
 */
void start_vm(vm_data_t *data)
{
    bool is_running = true;
    int current_cycle = 1;

    while (is_running) {
        for (int i = 0; i < MAX_PLAYERS; i++) {
            data->arena->players[i] ?
            exec_instruction_pforks(data->arena->players[i], data->arena) : 0;
        }
        if (current_cycle % data->arena->referee->cycle_to_die == 0)
            is_running = referee_checking(data);
        if (data->cmd_line_info->dump_nbr_cycle == current_cycle - 1)
            dump_mem(data);
        current_cycle++;
    }
}
/*
    // TO PRINT REGISTERS IN THE DUMP FUNCTION
    printf("\n");
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (data->arena->players[i] == NULL)
            continue;
        printf("[Player %d]\n", i + 1);
        int fork_nbr = 0;
        for (pfork_t *curr = data->arena->players[i]->forks; curr;
             curr = curr->next, fork_nbr++) {
            printf("Fork nbr %d (pc = %d) : ", fork_nbr, curr->pc);
            for (int j = 0; j < REG_NUMBER; j++) {
                printf("%d", curr->registers[j]);
                if (j + 1 != REG_NUMBER)
                    printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
*/
