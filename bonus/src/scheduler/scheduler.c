/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Scheduler
*/

#include <unistd.h>
#include "vm.h"

static void write_int8t_in_hex(u_int8_t nbr)
{
    const char *hex = "0123456789ABCDEF";

    write(1, &hex[nbr / 16], 1);
    write(1, &hex[nbr % 16], 1);
}

static void write_int16t_in_hex(u_int16_t nbr)
{
    write_int8t_in_hex(nbr / 256);
    write_int8t_in_hex(nbr % 256);
}

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

static void exec_instruction_pforks(vm_data_t *vdata, player_t *player, arena_t *arena)
{
    for (pfork_t *curr = player->forks; curr; curr = curr->next) {
        curr->cooldown = curr->cooldown == -1 ?
                find_instruction(
                        arena->battlefield[curr->pc % MEM_SIZE]).nbr_cycles :
                curr->cooldown;
        if (curr->cooldown == 0) {
            check_events(vdata->ndata, vdata);
            exec_instruction(vdata, curr, arena);
            usleep(5000);
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

void start_vm(vm_data_t *vdata)
{
    int current_cycle = 1;

    //FILE *debug1 = fopen("debug1.txt", "w");
    while (vdata->ndata->is_running) {
        //fprintf(debug1, "CYCLE %d\n", current_cycle);
        for (int i = 0; i < MAX_PLAYERS; i++) {
            vdata->arena->players[i] ?
            exec_instruction_pforks(vdata, vdata->arena->players[i], vdata->arena) : 0;
        }
        if (current_cycle % vdata->arena->referee->cycle_to_die == 0)
            vdata->ndata->is_running = referee_checking(vdata);
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
